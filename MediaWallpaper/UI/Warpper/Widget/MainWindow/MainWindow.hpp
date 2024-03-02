#pragma once
#include"UI/Base/Widget/Widget.hpp"

class QGridLayout;

namespace UI
{
	class SystemTrayIcon;
	class TerminalWidget;
	class PanelWidget;

	class MainWindow :public Widget
	{
		Q_OBJECT

	public:
		inline MainWindow(QWidget* parent = nullptr)
			:Widget(parent, Qt::Window)
		{
			this->allocation();
			this->connection();
			this->initialization();
		}

		virtual ~MainWindow() {}
	private:
		void quit();
		void allocation();
		void connection();
		void initialization();
	public:
		void updateStyleSheet();
		void updateLanguage();
		bool readInfo();
		void saveInfo();
	protected:
		void closeEvent(QCloseEvent* event) override;
	signals:
		void selectLanguage();
	private:
		TerminalWidget* Terminal = nullptr;
		PanelWidget* Panel = nullptr;

		SystemTrayIcon* TrayIcon = nullptr;
		QGridLayout* Layout = nullptr;
		bool QuitState = false;
	};
}
