#include"UI/Warpper/Widget/MainWindow/MainWindow.hpp"
#include"MediaWallPaper.hpp"
#include<QSessionManager>
#include<QSharedMemory>
#include<QStyleFactory>
#include<QSettings>
#include<thread>
#include<chrono>
#include<QFile>

using namespace UI;

MediaWallPaper::~MediaWallPaper()
{
	delete Window;
	Style = nullptr;
	Window = nullptr;
	WorkingState = false;
	while (StopState == false);
}

void MediaWallPaper::allocation()
{
	Memory.setNativeKey(QApplication::applicationName());
	Style = QStyleFactory::create("fusion");
	Window = new MainWindow();
}

void MediaWallPaper::connection()
{
	connect(this, &QApplication::commitDataRequest,
		this, [&](QSessionManager& manager)
		{
			Window->saveMediaData();
		},
		Qt::DirectConnection);
	connect(this, &MediaWallPaper::showWindow,
		Window, &MainWindow::show);
}

void MediaWallPaper::initialization()
{
	if (Memory.attach() == true)
	{
		AlreadyRunning = true;
		return;
	}

	QString appLink = Converter::CH("ÊÓÆµ±ÚÖ½²¥·ÅÆ÷") + ".lnk";
	QString appPath = this->applicationFilePath();
	QFile::link(appPath, appLink);
	Window->readMediaData();
	this->setStyle(Style);
	Memory.create(4);
}

void MediaWallPaper::listenThread()
{
	StopState = false;

	int* Int = nullptr;
	while (WorkingState)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		Int = static_cast<int*>(Memory.data());
		if (Int != nullptr && *Int == 0x01)
		{
			*Int = 0x00;
			emit this->showWindow();
		}
	}

	StopState = true;
}

int MediaWallPaper::exec()
{
	if (AlreadyRunning == true)
	{
		int* Int = static_cast<int*>(Memory.data());
		if (Int != nullptr)
		{
			*Int = 0x01;
		}

		return 0;
	}
	Window->show();
	Window->hide();
	WorkingState = true;

	std::thread(&MediaWallPaper::listenThread, this).detach();
	return QApplication::exec();
}
