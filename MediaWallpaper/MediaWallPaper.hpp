#pragma once
#include"UI/Warpper/Widget/MainWindow/MainWindow.hpp"
#include<QSharedMemory>
#include<QApplication>

namespace UI
{
	class MainWindow;

	class MediaWallpaper :public QApplication
	{
		Q_OBJECT

	public:
		inline MediaWallpaper(int argc, char** argv)
			:QApplication(argc, argv)
		{
			this->isRunning();
		}

		virtual ~MediaWallpaper();
	private:
		void isRunning();
		void allocation();
		void connection();
		void initialization();
	public:
		int exec();
	private:
		void createShortcut();
		void listenThread();
	signals:
		void showup();
	private:
		MainWindow* Window = nullptr;
		bool AlreadyRunning = false;
		bool ListenThread = false;
		bool StopState = true;
		QSharedMemory Memory;
	};
}
