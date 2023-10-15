#pragma once
#include"SubResources/TerminalGroupBoxRes.hpp"
#include"SubResources/BasicGroupBoxRes.hpp"
#include"SubResources/FileGroupBoxRes.hpp"
#include<QWidget>
#include<QFile>

namespace UI
{
	namespace image
	{
		const QString AutherIcon = "resources\\image\\AutherIcon.ico";

		const QString MainIcon = "resources\\image\\MainIcon.ico";
	}

	namespace css
	{
		//==========================================================================
		//Widgets and window

		const QString MainWindow = "resources\\css\\widget\\MainWindow.css";

		const QString PageWidget = "resources\\css\\widget\\PageWidget.css";

		const QString MediaWidget = "resources\\css\\widget\\MediaWidget.css";

		const QString PanelWidget = "resources\\css\\widget\\PanelWidget.css";

		const QString PlaylistWidget = "resources\\css\\widget\\PlaylistWidget.css";

		//==========================================================================
		//SystemTrayIcon

		const QString AboutMenu = "resources\\css\\trayIcon\\AboutMenu.css";
		const QString MainMenu = "resources\\css\\trayIcon\\MainMenu.css";

		//==========================================================================
		//Method

		inline bool Setter(const QString& Path, QWidget* Widget)
		{
			if (Widget == nullptr) return false;
			QString StyleSheet = "";
			QFile Reader(Path);

			if (Reader.open(QFile::ReadOnly))
			{
				StyleSheet = Reader.readAll();
				Widget->setStyleSheet(
					StyleSheet);
				return true;
			}

			return false;
		}
	}
}