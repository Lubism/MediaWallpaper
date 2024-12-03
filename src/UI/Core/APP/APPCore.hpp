#pragma once
#include<QApplication>

class QSharedMemory;

namespace UI
{
	class MainWindow;

	class APPCore :public QApplication
	{
		Q_OBJECT

	public:
		APPCore(int& argc, char** argv);

		virtual ~APPCore();
	private:
		void readInfo();
		void saveInfo();
		void appThread();

		void createShortcut();
		void checkDirExistance();
		void checkFileExistance();
		void initWindowGeometry();

		void allocation();
		void connection();
		void initialization();
	public:
		int initFailureMsg();
		int run();
	signals:
		/*
		* Notifing MainWindow to update the information of GUI
		* *For inner members*
		*/
		void transmitStreamInfo();

		void checkWindowState();

		/*
		* Notifing MainWindow to showup
		* *For inner members*
		*/
		void showup();
	private:
		QSharedMemory* Memory = nullptr;
		MainWindow* Window = nullptr;
		bool AlreadyRunning = false;
		bool FailState = false;

		bool TransmitState = false;
		bool ThreadState = false;
		bool OnThread = false;
	};
}
