#pragma once
#include"UI/Data/StreamInfo.hpp"

#include<QWidget>

#include<vector>
#include<mutex>

namespace UI
{
	class MediaPanel;

	class MediaCore :public QObject
	{
		Q_OBJECT

	public:
		inline explicit MediaCore(QWidget* parent = nullptr)
			:QObject(parent)
		{
			this->allocation();
		}

		virtual ~MediaCore();
	private:
		void allocation();
		void emitExportPlaylist();
	public:
		void receiveInfo(const StreamInfo& info);
		const StreamInfo& sendInfo();
		void updateStyleSheet();

		void loadFile(const QString& path);
		void setMonitor(int desktopID);
		void checkWindowState();

		void updatePlaylist();
		void loadAllConfig();
		void loadConfig();

		bool isRunning() const;
		void saveInfo() const;

		void clearInfo();
		void readInfo();

		void last();
		void next();
		void stop();
	signals:
		void exportPlaylist(const std::vector<QString>& playlist);
	private:
		std::vector<MediaPanel*> Panels;
		MediaPanel* Panel = nullptr;
		std::mutex Locker;

		int DesktopID = 0;
		StreamInfo EmptyInfo;
	};
}
