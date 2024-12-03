#pragma once
#include"UI/Data/StreamInfo.hpp"
#include<QTabWidget>

namespace UI
{
	class TerminalPanel;
	class PlaylistPanel;
	class DisplayPanel;
	class BasicPanel;
	class FilePanel;

	class GUICore :public QTabWidget
	{
		Q_OBJECT

	public:
		inline GUICore(QWidget* parent = nullptr)
			:QTabWidget(parent)
		{
			this->allocation();
			this->connection();
			this->initialization();
		}

		virtual ~GUICore();
	private:
		void allocation();
		void connection();
		void initialization();

		void fileConnection();
		void basicConnection();
		void displayConnection();
		void playlistConnection();
		void terminalConnection();
	public:
		void importPlaylist(const std::vector<QString>& playlist);
		void receiveInfo(const StreamInfo& info);
		void setMonitor(int index);

		void doUpdateStyleSheet();
		void doUpdateLanguage();
		void readInfo();
	signals:
		void sendInfo(const StreamInfo& info);
		void loadFile(const QString& path);
		void selectMonitor(int index);

		void updateStyleSheet();
		void updateLanaguage();
		void updatePlaylist();

		void loadAllConfig();
		void loadConfig();
		void clearInfo();

		void last();
		void next();
		void stop();
	private:
		TerminalPanel* Terminal = nullptr;
		PlaylistPanel* Playlist = nullptr;

		DisplayPanel* Display = nullptr;
		BasicPanel* Basic = nullptr;
		FilePanel* File = nullptr;

		StreamInfo Info;
	};
}
