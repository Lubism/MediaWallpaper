#pragma once
#include<QSystemTrayIcon>
#include<vector>

class QAction;
class QMenu;

namespace UI
{
	class SystemTrayIcon :public QSystemTrayIcon
	{
		using Int = long long;
		Q_OBJECT

	public:
		inline explicit SystemTrayIcon(QObject* parent = nullptr, const Int& screenCount = 1)
			:QSystemTrayIcon(parent), ScreenCount(screenCount)
		{
			this->allocation();
			this->connection();
			this->initialization();
		}

		inline virtual ~SystemTrayIcon() {}
	private:
		void allocation();
		void connection();
		void initialization();
	public:
		void updateLanguage();
	signals:
		void selectPanel(Int index);
		void terminal();
		void showup();
		void quit();
	private:
		Int ScreenCount = 1;

		QAction* Show = nullptr;
		QAction* Quit = nullptr;
		QAction* Screen = nullptr;
		QAction* Terminal = nullptr;

		QMenu* MainMenu = nullptr;
		QMenu* ScreenMenu = nullptr;
	};
}
