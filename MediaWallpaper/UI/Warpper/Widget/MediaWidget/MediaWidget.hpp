#pragma once
#include"UI/Warpper/MediaData/MediaData.hpp"
#include"mpvcpp/mpvProperty.hpp"
#include<QWidget>

namespace UI
{
	class MediaWidget :public QWidget
	{
		using EventID = mpv::code::EventID;
		using Format = mpv::code::Format;
		using Error = mpv::code::Error;
		using Property = mpv::Property;
		Q_OBJECT

	public:
		inline explicit MediaWidget(QWidget* parent = nullptr, const int& screenIndex = 0)
			:DesktopID(screenIndex), QWidget(parent)
		{
			this->allocation();
			this->connection();
			this->initialization();
		}

		virtual ~MediaWidget();
	private:
		void allocation();
		void connection() {}
		void initialization();
	public:
		bool loadfile(const QString& data);
		void updateStyleSheet();
		void loadConfig();
		void play();
		void last();
		void next();
		void stop();
	public:
		inline void subVisibility(bool& data) const { data = this->SubVisibility; }
		inline void playlistIndex(int& data) const { data = this->PlaylistIndex; }
		inline void duration(double& data) const { data = this->Duration; }
		inline void position(double& data) const { data = this->Position; }
		inline void playmode(int& data) const { data = this->Playmode; }
		inline void volume(double& data) const { data = this->Volume; }
		inline void speed(double& data) const { data = this->Speed; }
		inline void pause(bool& data) const { data = this->Pause; }
		inline void mute(bool& data) const { data = this->Mute; }

		inline void setSubVisibility(bool data);
		inline void setPlaylistIndex(int data);
		inline void setPosition(double data);
		inline void setPlaymode(int data);

		inline void setVolume(double data);
		inline void setSpeed(double data);
		inline void setPause(bool data);
		inline void setMute(bool data);

		inline void importData(MediaData& data);
		inline void exportData(MediaData& data);
		void refreshDisplay();
		void clearInfo();
	private:
		void setStartTime(double data);
		void importPlayfile();
		void listenThread();
		void eventThread();

		void eventFilter(mpv::Event* event,
			const int& code);
	signals:
		void updateTime(double _position_, double _duration_);
		void updatePlaylist(const std::vector<QString>& data);

		void updatePlaylistIndex(int index);
		void updatePlayfile(const QString& filename);
	private:
		static const std::unordered_map<std::string, int> PropertyKey;
		std::vector<QString> Playlist;
		std::string FolderPath = "";
		mpv::Handle Handle;

		bool ListenThread = false;
		bool EventThread = false;
		bool StopState = true;

		double Duration = 0.0;
		double Position = 0.0;
		double Volume = 100.0;
		double Speed = 1.0;

		int PlaylistIndex = -1;
		int DesktopID = 0;
		int Playmode = 0;

		bool SubVisibility = true;
		bool Pause = true;
		bool Mute = false;
	};

	inline void MediaWidget::setSubVisibility(bool data)
	{
		Property::Apply(Handle, "sub-visibility",
			data, DesktopID);
	}

	inline void MediaWidget::setPlaylistIndex(int data)
	{
		Property::Apply(Handle, "playlist-pos",
			std::to_string(data),
			DesktopID);
	}

	inline void MediaWidget::setPosition(double data)
	{
		Property::Apply(Handle, "playback-time",
			data, DesktopID);
	}

	inline void MediaWidget::setPlaymode(int data)
	{
		Playmode = data;
		switch (data)
		{
		case 0:	//	loop-playlist
			Property::Apply(Handle, "loop-playlist",
				"inf", DesktopID);
			Property::Apply(Handle, "loop-file",
				"no", DesktopID);
			break;
		case 1:	//	single loop
			Property::Apply(Handle, "loop-file",
				"inf", DesktopID);
			break;
		}
	}

	inline void MediaWidget::setVolume(double data)
	{
		Property::Apply(Handle, "volume",
			data, DesktopID);
	}

	inline void MediaWidget::setSpeed(double data)
	{
		Property::Apply(Handle, "speed",
			data, DesktopID);
	}

	inline void MediaWidget::setPause(bool data)
	{
		Property::Apply(Handle, "pause",
			data, DesktopID);
	}

	inline void MediaWidget::setMute(bool data)
	{
		Property::Apply(Handle, "mute",
			data, DesktopID);
	}

	inline void MediaWidget::importData(MediaData& data)
	{
		if (!this->loadfile(QString::fromStdString(data.FolderPath)))
			return;

		this->setSubVisibility(data.SubVisisbility);
		this->setPlaylistIndex(data.PlaylistIndex);
		this->setStartTime(data.Position);
		this->setPlaymode(data.Playmode);
		this->setVolume(data.Volume);
		this->setSpeed(data.Speed);
		this->setPause(data.Pause);
		this->setMute(data.Mute);
	}

	inline void MediaWidget::exportData(MediaData& data)
	{
		data.SubVisisbility = this->SubVisibility;
		data.PlaylistIndex = this->PlaylistIndex;
		data.FolderPath = this->FolderPath;
		data.Playmode = this->Playmode;
		data.Position = this->Position;
		data.Volume = this->Volume;
		data.Speed = this->Speed;
		data.Pause = this->Pause;
		data.Mute = this->Mute;
	}
}
