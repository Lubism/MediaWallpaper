#pragma once
#include<QSystemTrayIcon>

class QAction;
class QMenu;

namespace UI
{
	class SystemTrayIcon :public QSystemTrayIcon
	{
		using Reason = ActivationReason;
		Q_OBJECT

	public:
		inline SystemTrayIcon(QObject* parent = nullptr)
			:QSystemTrayIcon(parent)
		{
			this->allocation();
			this->connection();
			this->initialization();
		}

		virtual ~SystemTrayIcon();
	private:
		void allocation();
		void connection();
		void initialization();
	public:
		void updateStyleSheet();
	signals:
		void aboutProgram();
		void aboutAuther();
		void aboutIcon();

		void showup();
		void quit();
	private:
		QMenu* AboutMenu = nullptr;
		QMenu* MainMenu = nullptr;

		QAction* Program = nullptr;
		QAction* Auther = nullptr;
		QAction* Icon = nullptr;

		QAction* Show = nullptr;
		QAction* Quit = nullptr;
	};
}
