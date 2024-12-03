#include"UI/Data/TerminalInfo/TerminalInfo.hpp"
#include"UI/Data/ShellWindow/ShellWindow.hpp"
#include"UI/Data/DisplayInfo/DisplayInfo.hpp"
#include"UI/Data/ScreenInfo/ScreenInfo.hpp"
#include"UI/Data/Translator/Translator.hpp"

#include"UI/Surface/MainWindow/MainWindow.hpp"

#include<QSharedMemory>
#include<QMessageBox>
#include<QFile>
#include<QDir>

#include<chrono>
#include<thread>

#include"APPCore.hpp"

using namespace UI;

APPCore::APPCore(int& argc, char** argv)
	:QApplication(argc, argv)
{
	Memory = new QSharedMemory("$###||MediaWallpaper||###$", this);
	int size = sizeof(int);

	if (Memory->attach())
	{
		auto data = reinterpret_cast<int*>(Memory->data());
		if (data)
		{
			AlreadyRunning = true;
			*data = 0x01;
		}
	}
	else if (Memory->create(size))
	{
		auto data = reinterpret_cast<int*>(Memory->data());

		if (data) *data = 0x00;
	}
	else
	{
		FailState = true;
		return;
	}

	this->checkDirExistance();
	this->checkFileExistance();
}

APPCore::~APPCore()
{
	OnThread = false;
	while (ThreadState);

	Memory->detach();

	delete Window;
	Window = nullptr;
}

void APPCore::readInfo()
{
	ShellWindow::RefreshGeometry();
	ShellWindow::RefreshDisplay();
	ShellWindow::Init();

	auto ret = ShellWindow::AcqiureState();

	TerminalInfo::Read();
	DisplayInfo::Read();
	ScreenInfo::Read();
}

void APPCore::saveInfo()
{
	Window->saveInfo();
	ScreenInfo::Write();
	DisplayInfo::Write();
	TerminalInfo::Write();
}

void APPCore::appThread()
{
	ThreadState = true;

	int* data = nullptr;
	int tick = 1;
	while (OnThread)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1 << 7));
		if (TransmitState) emit this->transmitStreamInfo();
		emit this->checkWindowState();
		if (tick > 4)
		{
			data = reinterpret_cast<int*>(Memory->data());
			if (data && *data == 0x01) {
				emit this->showup();
				*data = 0x00;
			}

			tick >>= 3;
		}

		tick <<= 1;
	}

	ThreadState = false;
}

void APPCore::createShortcut()
{
	QString name = Translator::Acquire("MainWindow", "Main") + ".lnk";

	QFile file(name);
	if (file.exists()) return;
	QFile::link(this->applicationFilePath(), name);
}

void APPCore::checkDirExistance()
{
	auto execDir = [](QDir& ptr)
		{
			if (!ptr.exists())
			{
				ptr.mkdir(ptr.absolutePath());
			}
		};

	QDir mediaData("./mediaData");
	execDir(mediaData);

	QDir panelConfig("./mediaData/panelConfig");
	execDir(panelConfig);

	QDir resources("./resources");
	execDir(resources);

	QDir image("./resources/image");
	execDir(image);

	QDir stylesheet("./resources/stylesheet");
	execDir(stylesheet);

	QDir translation("./resources/translation");
	execDir(translation);
}

void APPCore::checkFileExistance()
{
	QFile mainIcon("./resources/image/Icon.png");
	if (!mainIcon.exists()) {
		FailState = true;
		return;
	}

	const QString stylesheet = "./resources/stylesheet";
	auto execFile = [](QFile& ptr)
		{
			if (ptr.open(QFile::NewOnly))
				ptr.close();
		};

	QFile basicPanel(stylesheet + "/BasicPanel.css");
	execFile(basicPanel);

	QFile filePanel(stylesheet + "./FilePanel.css");
	execFile(filePanel);

	QFile mainWindow(stylesheet + "./MainWindow.css");
	execFile(mainWindow);

	QFile mediaPanel(stylesheet + "./MediaPanel.css");
	execFile(mediaPanel);

	QFile displayPanel(stylesheet + "./DisplayPanel.css");
	execFile(displayPanel);

	QFile playlistPanel(stylesheet + "./PlaylistPanel.css");
	execFile(playlistPanel);

	QFile terminalPanel(stylesheet + "./TerminalPanel.css");
	execFile(terminalPanel);
}

void APPCore::initWindowGeometry()
{
	if (!Window) return;
	QRect result = Window->geometry();
	auto temp = ShellWindow::ScreenGeometry(0);

	auto shiftX = (temp.width() - result.width()) / 2;
	auto shiftY = (temp.height() - result.height()) / 2;
	result.setRect(shiftX, shiftY, result.width(), result.height());

	Window->setGeometry(result);
}

void APPCore::allocation()
{
	this->readInfo();
	Window = new MainWindow();
}

void APPCore::connection()
{
	connect(this, &QApplication::commitDataRequest, this,
		[&](QSessionManager&) {
			this->saveInfo();
		});

	connect(this, &APPCore::transmitStreamInfo, Window,
		&MainWindow::transmitStreamInfo);
	connect(this, &APPCore::checkWindowState, Window,
		&MainWindow::checkWindowState);
	connect(this, &APPCore::showup, Window,
		&MainWindow::showup);

	connect(Window, &MainWindow::windowHidden, this,
		[&]() {TransmitState = false; });
	connect(Window, &MainWindow::windowShowed, this,
		[&]() {TransmitState = true; });
	connect(Window, &MainWindow::shutdown, this,
		&APPCore::saveInfo);
}

void APPCore::initialization()
{
	OnThread = true;
	this->setStyle("fusion");
	std::thread(&APPCore::appThread, this).detach();
}

int APPCore::initFailureMsg()
{
	QString title = "MediaWallpaper: Fatal Error";

	QString prefix = "Fail to load the program, there are two possible ways to fix this issue:\n";

	QString methodOne = "1. Check the memory of the computer and try to free some space for this program.\n";
	QString methodTwo = "2. Check the existance of icon file (Location: ~/resources/image/Icon.png).\n";

	QString suffix = "\nThis program will exit with code -32768 after closing this notification.";

	auto temp = QMessageBox::critical(nullptr, title, prefix + methodOne + methodTwo + suffix,
		QMessageBox::StandardButton::Close);

	return -32768;
}

int APPCore::run()
{
	if (FailState) return this->initFailureMsg();
	if (AlreadyRunning)
		return 0;

	this->allocation();
	this->connection();
	this->initialization();

	bool state = Window->readInfo();
	this->initWindowGeometry();
	Window->show();

#ifndef _DEBUG
	if (state) Window->close();
#endif // _DEBUG

	this->createShortcut();
	return this->exec();
}
