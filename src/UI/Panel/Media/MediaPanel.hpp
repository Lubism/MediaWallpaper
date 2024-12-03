#pragma once
#include"UI/Basic/MediaWidget.hpp"

#include"UI/Data/StreamInfo.hpp"

#include"mpvcpp/mpvProperty.hpp"

namespace UI
{
	class MediaPanel :public MediaWidget
	{
	private:
		using Property = mpv::Property;
	public:
		inline MediaPanel(int monitorID = 0, QWidget* parent = nullptr)
			:MediaWidget(monitorID, parent)
		{
			this->initialization();
		}

		inline virtual ~MediaPanel() {}
	private:
		std::vector<QString> exportPlaylist(const std::vector<QString>& fileList) const;
		std::vector<QString> analyzeDirectory(const QString& path) const;

		void initialization();
	public:
		inline std::vector<QString> playlist() const { return Playlist; }
		inline bool isFileLoaded() const { return FileLoadedState; }
		inline void setStreamInfo(const StreamInfo& info);
		inline const StreamInfo& streamInfo();
		inline void loadConfig();

		void checkWindowState(int state);
		void updateStyleSheet();
		void updatePlaylist();
		void clearInfo();
		void saveInfo();
		void readInfo();

		void loadFile(const std::vector<QString>& playlist, const QString& dirPath);
		void loadFile(const QString& path);

		void play();
		void stop();
	private:
		const static std::string ConfigPrefix;
		const static std::string ConfigSuffix;

		std::vector<QString> Playlist;
		bool FileLoadedState = false;
		StreamInfo Info;
	};

	inline void MediaPanel::setStreamInfo(const StreamInfo& info)
	{
		if (info.Index > -1) this->setPlaylistPosition(info.Index);

		if (info.Position >= 0.0 && info.Position != Info.Position)
			this->setPosition(info.Position);
		if (info.Volume >= 0.0) this->setVolume(info.Volume);
		if (info.Speed >= 0.0) this->setSpeed(info.Speed);

		this->setSubVisibility(info.Subtitle);
		this->setPlaymode(info.Playmode);
		this->setPause(info.Pause);
		this->setMute(info.Mute);

		auto& dpy = info.Display;

		this->setBrightness(dpy.Brightness);
		this->setSaturation(dpy.Saturation);
		this->setContrast(dpy.Contrast);

		this->setRotate(dpy.Rotate);
		this->setGamma(dpy.Gamma);
		this->setHue(dpy.Hue);

		this->setAspectRatio(dpy.AspectRatio);
		this->setPanscan(dpy.Panscan);

		this->setAlign(dpy.HAlign, dpy.VAlign);
		this->setFlip(dpy.HFlip, dpy.VFlip);

		if (FileLoadedState && !info.Pause && this->isHidden())
			this->play();

		Info.AtFullscreen = info.AtFullscreen;
		Info.AtFocus = info.AtFocus;
	}

	inline const StreamInfo& MediaPanel::streamInfo()
	{
		this->playlistPosition(Info.Index);
		this->duration(Info.Duration);
		this->position(Info.Position);
		this->volume(Info.Volume);
		this->speed(Info.Speed);

		this->subVisibility(Info.Subtitle);
		this->playmode(Info.Playmode);
		this->pause(Info.Pause);
		this->mute(Info.Mute);

		if (Info.Index > -1 && Info.Index < Playlist.size())
			Info.Name = Playlist.at(Info.Index);
		auto& dpy = Info.Display;

		this->brightness(dpy.Brightness);
		this->saturation(dpy.Saturation);
		this->contrast(dpy.Contrast);

		this->rotate(dpy.Rotate);
		this->gamma(dpy.Gamma);
		this->hue(dpy.Hue);

		this->aspectRatio(dpy.AspectRatio);
		this->panscan(dpy.Panscan);

		this->align(dpy.HAlign, dpy.VAlign);
		this->flip(dpy.HFlip, dpy.VFlip);

		return Info;
	}

	inline void MediaPanel::loadConfig()
	{
		const std::string content = std::to_string(MonitorID);
		Handle.loadConfig(ConfigPrefix + content + ConfigSuffix);
	}
}
