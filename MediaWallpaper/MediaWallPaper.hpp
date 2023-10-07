#pragma once
#include<QSharedMemory>
#include<QApplication>

class QStyle;

namespace UI
{
	class MainWindow;

	class MediaWallPaper :public QApplication
	{
		Q_OBJECT

	public:
		inline MediaWallPaper(int& argc, char** argv)
			:QApplication(argc, argv)
		{
			this->allocation();
			this->connection();
			this->initialization();
		}

		virtual ~MediaWallPaper();
	private:
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
		QStyle* Style = nullptr;

		bool AlreadyRunning = false;
		bool WorkingState = false;
		bool StopState = true;
		QSharedMemory Memory;
	};
}