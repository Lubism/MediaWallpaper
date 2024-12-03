#pragma once
#include"UI/Basic/Widget.hpp"

class QGridLayout;

namespace UI
{
	class SystemTrayIcon;
	class MediaCore;
	class DataCore;
	class GUICore;

	class MainWindow :public Widget
	{
		Q_OBJECT

	public:
		inline explicit MainWindow(QWidget* parent = nullptr)
			:Widget(parent)
		{
			this->allocation();
			this->connection();
			this->initialization();
		}

		virtual ~MainWindow();
	private:
		void allocation();
		void connection();
		void initialization();

		void guiConnection();
		void mediaConnection();
		void trayIconConnection();
	public:
		void transmitStreamInfo();
		void checkWindowState();
		void updateStyleSheet();
		void updateLanguage();

		void saveInfo() const;
		bool readInfo();

		inline void showup();
	protected:
		void closeEvent(QCloseEvent* event) override;
		void hideEvent(QHideEvent* event) override;
		void showEvent(QShowEvent* event) override;
	signals:
		void windowHidden();
		void windowShowed();
		void shutdown();
	private:
		SystemTrayIcon* TrayIcon = nullptr;
		QGridLayout* Layout = nullptr;

		MediaCore* Media = nullptr;
		GUICore* Gui = nullptr;

		QIcon* Icon = nullptr;
		bool Shutdown = false;
	};

	inline void MainWindow::showup()
	{
		if (this->isMinimized())
		{
			if (this->isMaximized())
			{
				this->showMaximized();
			}
			else
			{
				this->showNormal();
			}
		}

		this->show();
	}
}
