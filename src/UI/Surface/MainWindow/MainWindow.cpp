#include"UI/Surface/SystemTrayIcon/SystemTrayIcon.hpp"

#include"UI/Data/TerminalInfo/TerminalInfo.hpp"
#include"UI/Data/ShellWindow/ShellWindow.hpp"
#include"UI/Data/Translator/Translator.hpp"
#include"UI/Data/StyleSheet.hpp"

#include"UI/Core/Media/MediaCore.hpp"
#include"UI/Core/GUI/GUICore.hpp"

#include<QCloseEvent>
#include<QGridLayout>
#include<QIcon>

#include"MainWindow.hpp"

using namespace std::this_thread;
using namespace std::chrono;
using namespace UI;

MainWindow::~MainWindow()
{
	delete Icon;
	Icon = nullptr;
}

void MainWindow::allocation()
{
	Icon = new QIcon("./resources/image/Icon.png");

	TrayIcon = new SystemTrayIcon(this);
	Layout = new QGridLayout(this);
	Media = new MediaCore(this);
	Gui = new GUICore(this);
}

void MainWindow::connection()
{
	this->guiConnection();
	this->mediaConnection();
	this->trayIconConnection();
}

void MainWindow::initialization()
{
	this->setWindowTitle("MediaWallpaper");
	this->setMinimumSize(660, 280);
	this->setWindowIcon(*Icon);
	this->updateStyleSheet();
	this->updateLanguage();

	TrayIcon->setIcon(*Icon);
	Layout->addWidget(Gui);
	TrayIcon->show();
}

void MainWindow::guiConnection()
{
	connect(Gui, &GUICore::last, Media, &MediaCore::last);
	connect(Gui, &GUICore::next, Media, &MediaCore::next);
	connect(Gui, &GUICore::stop, Media, &MediaCore::stop);

	connect(Gui, &GUICore::clearInfo, Media, &MediaCore::clearInfo);
	connect(Gui, &GUICore::loadConfig, Media, &MediaCore::loadConfig);
	connect(Gui, &GUICore::loadAllConfig, Media, &MediaCore::loadAllConfig);

	connect(Gui, &GUICore::loadFile, Media, &MediaCore::loadFile);
	connect(Gui, &GUICore::sendInfo, Media, &MediaCore::receiveInfo);
	connect(Gui, &GUICore::selectMonitor, Media, &MediaCore::setMonitor);

	connect(Gui, &GUICore::updatePlaylist, Media, &MediaCore::updatePlaylist);
	connect(Gui, &GUICore::updateLanaguage, this, &MainWindow::updateLanguage);
	connect(Gui, &GUICore::updateStyleSheet, this, &MainWindow::updateStyleSheet);
}

void MainWindow::mediaConnection()
{
	connect(Media, &MediaCore::exportPlaylist, Gui, &GUICore::importPlaylist);
}

void MainWindow::trayIconConnection()
{
	connect(TrayIcon, &SystemTrayIcon::monitorSelected, Media, &MediaCore::setMonitor);
	connect(TrayIcon, &SystemTrayIcon::monitorSelected, Gui, &GUICore::setMonitor);
	connect(TrayIcon, &SystemTrayIcon::shutdown, this, [&]() {
		Shutdown = true;
		this->show();	// Update internal mark
		this->close();
		});
	connect(TrayIcon, &SystemTrayIcon::terminal, this, [&]() {
		Gui->setCurrentIndex(4);
		this->showup();
		});
	connect(TrayIcon, &SystemTrayIcon::showup, this,
		&MainWindow::showup);
}

void MainWindow::transmitStreamInfo()
{
	Gui->receiveInfo(Media->sendInfo());
}

void MainWindow::checkWindowState()
{
	Media->checkWindowState();
}

void MainWindow::updateStyleSheet()
{
	StyleSheet::Set(this, "MainWindow");
	TrayIcon->updateStyleSheet();

	Gui->doUpdateStyleSheet();
	Media->updateStyleSheet();
}

void MainWindow::updateLanguage()
{
	auto title = Translator::Acquire("MainWindow", "Main");

#ifdef _DEBUG
	title.append(QString("(Debug)"));
#endif // _DEBUG

	/*Testing: self-exclude*/
	ShellWindow::AddExcludeHandle(title);
	this->setWindowTitle(title);
	TrayIcon->updateLanguage();
	Gui->doUpdateLanguage();
}

void MainWindow::saveInfo() const
{
	TerminalInfo::ImportRect(this->rect());
	Media->saveInfo();
}

bool MainWindow::readInfo()
{
	this->resize(TerminalInfo::Width, TerminalInfo::Height);
	Media->readInfo();
	Gui->readInfo();

	return Media->isRunning();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	if (Shutdown)
	{
		emit this->shutdown();
		event->accept();
		return;
	}

	this->hide();
	event->ignore();
}

void MainWindow::showEvent(QShowEvent* event)
{
	emit this->windowShowed();
	Widget::showEvent(event);
}

void MainWindow::hideEvent(QHideEvent* event)
{
	emit this->windowHidden();
	Widget::hideEvent(event);
}
