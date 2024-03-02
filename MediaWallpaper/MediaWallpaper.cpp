#include"UI/Warpper/Data/DesktopInfo/DesktopInfo.hpp"
#include"UI/Warpper/Data/Translator/Translator.hpp"
#include<QStyleFactory>
#include<QFile>
#include<QDir>

#include<thread>
#include<chrono>

#include"MediaWallpaper.hpp"

using namespace UI;
using namespace std;

MediaWallpaper::~MediaWallpaper()
{
	delete Window;
	Window = nullptr;

	StopState = true;
	while (ListenThread);
}

void MediaWallpaper::isRunning()
{
	Memory.setNativeKey("$#MediaWallpaper#$");
	if (Memory.attach() == true)
	{
		AlreadyRunning = true;
		return;
	}

	auto root = "./mediaData";
	auto sub = "config";

	QDir().mkdir(root);
	QDir(root).mkdir(sub);

	this->allocation();
	this->connection();
	this->initialization();
}

void MediaWallpaper::allocation()
{
	Window = new MainWindow;
	this->setStyle(QStyleFactory::create("fusion"));
}

void MediaWallpaper::connection()
{
	connect(this, &MediaWallpaper::commitDataRequest,
		this, [&](QSessionManager&)
		{
			Window->saveInfo();
		});

	connect(Window, &MainWindow::selectLanguage, this,
		&MediaWallpaper::createShortcut);
	connect(this, &MediaWallpaper::showup, Window,
		&MainWindow::showup);
}

void MediaWallpaper::initialization()
{
	StopState = false;
	Memory.create(sizeof(int));
	auto rect = DesktopInfo::screenGeometry(0);
	std::thread(&MediaWallpaper::listenThread, this).detach();

	auto position = [](int left, int right) {return (left - right) / 2; };
	Window->move(position(rect.width(), Window->width()),
		position(rect.height(), Window->height())
	);
}

int MediaWallpaper::exec()
{
	if (AlreadyRunning)
	{
		int* sign = static_cast<int*>(Memory.data());
		if (sign != nullptr)
		{
			*sign = 0x01;
			return 0;
		}
	}

	Window->showup();
	if (Window->readInfo())
	{
		Window->hide();
	}

	return QApplication::exec();
}

void MediaWallpaper::createShortcut()
{
	if (!Translator::TranslationAvaliable()) return;
	QString name = Translator::Acquire("MainGroup",
		"Main") + ".lnk";

	QFile file(name);
	if (file.exists()) return;
	QFile::link(this->applicationFilePath(), name);
}

void MediaWallpaper::listenThread()
{
	ListenThread = true;

	int* sign = nullptr;
	while (!StopState)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1 << 9));
		sign = static_cast<int*>(Memory.data());
		if (sign && *sign == 0x01)
		{
			emit this->showup();
			*sign = 0x00;
		}
	}

	ListenThread = false;
}
