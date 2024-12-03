#pragma once
#include<QSystemTrayIcon>

#include<vector>

class QAction;
class QMenu;

namespace UI
{
	class SystemTrayIcon :public QSystemTrayIcon
	{
		Q_OBJECT

	public:
		inline explicit SystemTrayIcon(QObject* parent = nullptr)
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
		void updateLanguage();
	signals:
		void monitorSelected(int screenIndex);
		void terminal();
		void shutdown();
		void showup();
	private:
		QMenu* MonitorMenu = nullptr;
		QMenu* MainMenu = nullptr;

		std::vector<QAction*> Monitor;
		QAction* Terminal = nullptr;
		QAction* Shutdown = nullptr;
		QAction* Showup = nullptr;
	};
}
