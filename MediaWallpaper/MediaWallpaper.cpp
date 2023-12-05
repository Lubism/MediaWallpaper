#include"UI/Warpper/Widget/MainWindow/MainWindow.hpp"
#include "MediaWallpaper.hpp"
#include<QStyleFactory>
#include<QFile>

#include<thread>
#include<chrono>

using namespace UI;
using namespace std;

MediaWallpaper::~MediaWallpaper()
{
	delete Window;
	Window = nullptr;
	WorkingState = false;
	while (StopState == false);
}

void MediaWallpaper::isRunning()
{
	Memory.setNativeKey(QApplication::applicationName());
	if (Memory.attach() == true)
	{
		AlreadyRunning = true;
		return;
	}

	this->allocation();
	this->connection();
	this->initialization();
}

void MediaWallpaper::allocation()
{
	this->setStyle(QStyleFactory::create("fusion"));
	Window = new MainWindow;
}

void MediaWallpaper::connection()
{
	connect(this, &MediaWallpaper::commitDataRequest, this,
		[&](QSessionManager& manager)
		{
			Window->saveMediaData();
		},
		Qt::DirectConnection);
	connect(this, &MediaWallpaper::showWindow,
		Window, &MainWindow::show);
}

void MediaWallpaper::initialization()
{
	QString appLink = QString::fromUtf8("\350\247\206\351\242\221\345\243\201\347\272\270\346\222\255\346\224\276\345\231\250");
	QString appPath = QApplication::applicationFilePath();
	QFile::link(appPath, appLink + ".lnk");
	Window->readMediaData();
	Memory.create(4);
}

void MediaWallpaper::listenThread()
{
	StopState = false;

	int* Int = nullptr;
	while (WorkingState)
	{
		this_thread::sleep_for(chrono::milliseconds(1 << 9));
		Int = static_cast<int*>(Memory.data());
		if (Int != nullptr && *Int == 0x01)
		{
			*Int = 0x00;
			emit this->showWindow();
		}
	}

	StopState = true;
}

int MediaWallpaper::exec()
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

	std::thread(&MediaWallpaper::listenThread, this).detach();
	return QApplication::exec();
}
