#pragma once
#include"mpvcpp/mpvProperty.hpp"
#include"mpvcpp/mpvCommand.hpp"
#include<unordered_map>
#include<QWidget>

namespace UI
{
	class MediaWidget: public QWidget
	{
		using EventID = mpv::code::EventID;
		using Format = mpv::code::Format;
		using Error = mpv::code::Error;
		using Property = mpv::Property;
		using Int = long long;

		Q_OBJECT

	public:
		inline explicit MediaWidget(QWidget* parent = nullptr, const Int& screenIndex = 0)
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
		bool loadFile(const QString& data);
		void updateStyleSheet();
		void refreshDisplay();
		void loadConfig();
		void clearInfo();
		void play();
		void stop();
	public:
		inline void setSubVisibility(bool data) { Property::Apply(Handle, "sub-visibility", data, DesktopID); }
		inline void setCurrentIndex(Int data) { Property::Apply(Handle, "playlist-pos", data, DesktopID); }
		inline void setPosition(double data) { Property::Apply(Handle, "playback-time", data, DesktopID); }

		inline void setPlaymode(Int data);
		bool setStartTime(double data);
		void setPause(bool data);

		inline void setVolume(double data) { Property::Apply(Handle, "volume", data, DesktopID); }
		inline void setSpeed(double data) { Property::Apply(Handle, "speed", data, DesktopID); }
		inline void setMute(bool data) { Property::Apply(Handle, "mute", data, DesktopID); }

		inline void last() { mpv::Command::Async(Handle, { "playlist-prev" }, DesktopID); }
		inline void next() { mpv::Command::Async(Handle, { "playlist-next" }, DesktopID); }
	public:
		inline void pause(bool& data) const { Property::Acquire(Handle, "pause", data); }
		inline void directory(QString& data) const { data = DirectoryPath; }

		inline void subVisibility(bool& data) const { data = SubVisibility; }
		inline void currentIndex(Int& data) const { data = CurrentIndex; }
		inline void position(double& data) const { data = Position; }
		inline void duration(double& data) const { data = Duration; }
		inline void playmode(Int& data) const { data = Playmode; }

		inline void volume(double& data) const { data = Volume; }
		inline void speed(double& data) const { data = Speed; }
		inline void mute(bool& data) const { data = Mute; }
	private:
		static std::vector<QString> analyzeDirectory(const QString& dirPath);
		inline void emitThread();
		void importPlaylist();
		void eventThread();
	signals:
		void updatePlaylist(const std::vector<QString>& data);
		void updateTime(double position, double duration);
		void currentFileChanged(const QString& filename);

		void updateSubVisibility(bool data);
		void updateCurrentIndex(Int index);
		void updatePlaymode(Int data);

		void updateDirectory(const QString& data);
		void updateVolume(double data);
		void updateSpeed(double data);
		void updateMute(bool data);
	private:
		std::vector<QString> Playlist;
		QString DirectoryPath = "";
		bool EventThread = false;
		bool StopState = true;
		mpv::Handle Handle;

		double Duration = 0.0;
		double Position = 0.0;
		double Volume = 0.0;
		double Speed = 0.0;

		Int CurrentIndex = 0;
		Int DesktopID = 0;
		Int Playmode = 0;

		bool SubVisibility = true;
		bool Mute = false;
	};

	inline void MediaWidget::setPlaymode(Int data)
	{
		Playmode = data;
		switch (data)
		{
		case 0LL: // loop-playlist
			Property::Apply(Handle, "loop-playlist",
				"inf", DesktopID);
			Property::Apply(Handle, "loop-file",
				"no", DesktopID);
			break;
		case 1LL: // single loop
			Property::Apply(Handle, "loop-file",
				"inf", DesktopID);
			break;
		}
	}

	inline void MediaWidget::emitThread()
	{
		emit this->updateSubVisibility(SubVisibility);
		emit this->updateTime(Position, Duration);
		emit this->updatePlaymode(Playmode);
		emit this->updateVolume(Volume);
		emit this->updateSpeed(Speed);
		emit this->updateMute(Mute);
	}
}
