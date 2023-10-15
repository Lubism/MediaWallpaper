#pragma once
#include<QSharedMemory>
#include<QApplication>

namespace UI
{
	class MainWindow;

	class MediaWallpaper :public QApplication
	{
		Q_OBJECT

	public:
		inline MediaWallpaper(int& argc, char**& argv)
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
	private:
		void listenThread();
	public:
		int exec();
	signals:
		void showWindow();
	private:
		UI::MainWindow* Window = nullptr;
		bool AlreadyRunning = false;
		bool WorkingState = false;
		bool StopState = true;
		QSharedMemory Memory;
	};
}
