#pragma once
#include"UI/Basic/Widget/Widget.hpp"

namespace UI
{
	class TerminalGroupBox;
	class SystemTrayIcon;
	class PanelWidget;
	class MessageBox;

	class MainWindow :public Widget
	{
		Q_OBJECT

	public:
		inline explicit MainWindow(QWidget* parent = nullptr)
			:Widget(parent, Qt::Window)
		{
			this->allocation();
			this->connection();
			this->initialization();
		}
	private:
		void allocation();
		void connection();
		void initialization();
	public:
		void readMediaData();
		void saveMediaData();
		void updateStyleSheet();
		void setAutoBoot(bool data);
		void makeAutobootFile(bool data);
	protected:
		void resizeEvent(QResizeEvent* event) override;
		void closeEvent(QCloseEvent* event) override;
		inline void quit();
	private:
		TerminalGroupBox* Terminal = nullptr;
		SystemTrayIcon* TrayIcon = nullptr;
		PanelWidget* Panel = nullptr;

		MessageBox* AboutProgram = nullptr;
		MessageBox* AboutAuther = nullptr;
		MessageBox* AboutIcon = nullptr;

		bool AutobootState = false;
		bool QuitState = false;
	};

	inline void MainWindow::quit()
	{
		QuitState = true;
		this->close();
	}
}
