#pragma once
#include<QObject>
#include<string>

namespace UI
{
	class MediaData :public QObject
	{
	public:
		std::string FolderPath = "";
		bool SubVisisbility = true;
		int WidgetHeight = 280;
		int WidgetWidth = 560;
		int PlaylistIndex = 0;
		double Position = 0.0;
		double Volume = 100.0;
		double Speed = 1.0;
		bool Pause = false;
		bool Mute = false;
		int Playmode = 0;
	public:
		MediaData(QObject* parent = nullptr,
			const int& screenIndex = 0);
		inline virtual ~MediaData() {}

		void read();
		void save();
		void clearInfo();
	private:
		int ScreenIndex = 0;
	};
}