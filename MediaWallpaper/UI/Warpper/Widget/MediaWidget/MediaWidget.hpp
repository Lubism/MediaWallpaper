#pragma once
#include"UI/Warpper/MediaData/MediaData.hpp"
#include"client/mpvProperty.hpp"
#include<QWidget>

namespace UI
{
	class MediaWidget :public QWidget
	{
		using Property = mpv::client::Property;
		using Format = mpv::client::Format;
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
		void loadfile(const QString& data);
		void loadconfig();
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
		void acquireThread();
		void eventThread();
		void eventFilter(mpv::client::Event* event, int& code);
	signals:
		void updateTime(double _position_, double _duration_);
		void updatePlaylist(const std::vector<QString>& data);

		void updatePlaylistIndex(int index);
		void updatePlayfile(const QString& filename);
	private:
		std::vector<QString> Playlist;
		std::string FolderPath = "";
		mpv::client::Handle Handle;
		bool AcquireThread = false;
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
		Property::apply(Handle, "sub-visibility",
			Format::BooleanInt, data,
			DesktopID);
	}

	inline void MediaWidget::setPlaylistIndex(int data)
	{
		Property::apply(Handle, "playlist-pos", Format::String,
			std::to_string(data), DesktopID);
	}

	inline void MediaWidget::setPosition(double data)
	{
		Property::apply(Handle, "playback-time",
			Format::Double, data,
			DesktopID);
	}

	inline void MediaWidget::setPlaymode(int data)
	{
		Playmode = data;
		switch (data)
		{
		case 0:	//	loop-playlist
			Property::apply(Handle, "loop-playlist",
				Format::String, "inf",
				DesktopID);
			Property::apply(Handle, "loop-file",
				Format::String, "no",
				DesktopID);
			break;
		case 1:	//	single loop
			Property::apply(Handle, "loop-file",
				Format::String, "inf",
				DesktopID);
			break;
		}
	}

	inline void MediaWidget::setVolume(double data)
	{
		Property::apply(Handle, "volume",
			Format::Double, data,
			DesktopID);
	}

	inline void MediaWidget::setSpeed(double data)
	{
		Property::apply(Handle, "speed",
			Format::Double, data,
			DesktopID);
	}

	inline void MediaWidget::setPause(bool data)
	{
		Property::apply(Handle, "pause",
			Format::BooleanInt, data,
			DesktopID);
	}

	inline void MediaWidget::setMute(bool data)
	{
		Property::apply(Handle, "mute",
			Format::BooleanInt, data,
			DesktopID);
	}

	inline void MediaWidget::importData(MediaData& data)
	{
		if (data.FolderPath.empty())
			return;

		this->loadfile(QString::fromStdString(data.FolderPath));
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