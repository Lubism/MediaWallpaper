#pragma once
#include"mpvcpp/mpvProperty.hpp"
#include"mpvcpp/mpvCommand.hpp"

#include"Widget.hpp"

namespace UI
{
	class MediaWidget :public Widget
	{
	protected:
		using Property = mpv::Property;
		using Command = mpv::Command;
		using Node = mpv::Node;
		using Int = long long;
	protected:
		inline explicit MediaWidget(int monitorID, QWidget* parent = nullptr)
			:Widget(parent, Qt::ToolTip | Qt::FramelessWindowHint),
			MonitorID(monitorID)
		{
			Handle.create();
			Handle.initialize();
		}

		inline virtual ~MediaWidget() {}
	public:
		inline void last() const { Command::Sync(Handle, { "playlist-prev" }); }
		inline void next() const { Command::Sync(Handle, { "playlist-next" }); }
		inline void hiddenShow() { this->show(); this->hide(); }
	protected:
		inline void setAspectRatio(const double& data) const { Property::Apply(Handle, "video-aspect-override", data); }
		inline void setPanscan(const double& data) const { Property::Apply(Handle, "panscan", data); }

		inline void setBrightness(const Int& data) const { Property::Apply(Handle, "brightness", data); }
		inline void setSaturation(const Int& data) const { Property::Apply(Handle, "saturation", data); }
		inline void setRotate(const Int& data) const { Property::Apply(Handle, "video-rotate", data); }

		inline void setContrast(const Int& data) const { Property::Apply(Handle, "contrast", data); }
		inline void setGamma(const Int& data) const { Property::Apply(Handle, "gamma", data); }
		inline void setHue(const Int& data) const { Property::Apply(Handle, "hue", data); }

		inline void setPlaylistPosition(const Int& data) const { Property::Apply(Handle, "playlist-pos", data); }
		inline void setSubVisibility(const bool& data) const { Property::Apply(Handle, "sub-visibility", data); }

		inline void setPosition(const double& data) const { Property::Apply(Handle, "playback-time", data); }
		inline void setVolume(const double& data) const { Property::Apply(Handle, "volume", data); }
		inline void setSpeed(const double& data) const { Property::Apply(Handle, "speed", data); }

		inline void setPause(const bool& data) const { Property::Apply(Handle, "pause", data); }
		inline void setMute(const bool& data) const { Property::Apply(Handle, "mute", data); }

		inline void setAlign(const double& halign, const double& valign) const;
		inline void setFlip(const bool& hflip, const bool& vflip) const;

		inline void setStartTime(const double& data) const;
		inline void setPlaymode(const Int& data) const;
	protected:
		inline void aspectRatio(double& data) const { Property::Acquire(Handle, "video-aspect-override", data); }
		inline void panscan(double& data) const { Property::Acquire(Handle, "panscan", data); }

		inline void brightness(Int& data) const { Property::Acquire(Handle, "brightness", data); }
		inline void saturation(Int& data) const { Property::Acquire(Handle, "saturation", data); }
		inline void rotate(Int& data) const { Property::Acquire(Handle, "video-rotate", data); }

		inline void contrast(Int& data) const { Property::Acquire(Handle, "contrast", data); }
		inline void gamma(Int& data) const { Property::Acquire(Handle, "gamma", data); }
		inline void hue(Int& data) const { Property::Acquire(Handle, "hue", data); }

		inline void playlistPosition(Int& data) const { Property::Acquire(Handle, "playlist-pos", data); }
		inline void subVisibility(bool& data) const { Property::Acquire(Handle, "sub-visibility", data); }

		inline void position(double& data) const { Property::Acquire(Handle, "playback-time", data); }
		inline void duration(double& data) const { Property::Acquire(Handle, "duration", data); }
		inline void volume(double& data) const { Property::Acquire(Handle, "volume", data); }
		inline void speed(double& data) const { Property::Acquire(Handle, "speed", data); }

		inline void pause(bool& data) const { Property::Acquire(Handle, "pause", data); }
		inline void mute(bool& data) const { Property::Acquire(Handle, "mute", data); }

		inline void align(double& halign, double& valign) const;
		inline void flip(bool& hflip, bool& vflip) const;
		inline void playmode(Int& data) const;
	protected:
		inline void importPlaylist(const std::vector<QString>& data) const noexcept;
	protected:
		mpv::Handle Handle;
		int MonitorID = 0;
	};

	// =========================================================================================

	inline void MediaWidget::setAlign(const double& halign, const double& valign) const
	{
		Property::Apply(Handle, "video-align-x", halign);
		Property::Apply(Handle, "video-align-y", valign);
	}

	inline void MediaWidget::setFlip(const bool& hflip, const bool& vflip) const
	{
		static std::string temp;
		temp.clear();

		if (hflip) temp += "hflip";

		if (vflip)
		{
			if (hflip) temp += ",";
			temp += "vflip";
		}

		Property::Apply(Handle, "vf", temp);
	}

	inline void MediaWidget::setStartTime(const double& data) const
	{
		double target = static_cast<double>(static_cast<long long>(data));
		if (target <= 0.0) return;
		double temp = 0.0;

		while (0 == static_cast<long long>(temp))
		{
			Property::Apply(Handle, "time-pos", target);
			Property::Acquire(Handle, "time-pos", temp);
		}
	}

	inline void MediaWidget::setPlaymode(const Int& data) const
	{
		switch (data)
		{
		case 0LL: // loop-playlist
			Property::Apply(Handle, "loop-playlist", "inf");
			Property::Apply(Handle, "loop-file", "no");
			break;
		case 1LL: // single loop
			Property::Apply(Handle, "loop-file", "inf");
			break;
		}
	}

	// =========================================================================================

	inline void MediaWidget::align(double& halign, double& valign) const
	{
		Property::Acquire(Handle, "video-align-x", halign);
		Property::Acquire(Handle, "video-align-y", valign);
	}

	inline void MediaWidget::flip(bool& hflip, bool& vflip) const
	{
		static std::string temp;
		hflip = vflip = false;
		temp.clear();

		Property::Acquire(Handle, "vf", temp);

		if (temp.find("hflip") != std::string::npos)
			hflip = true;
		if (temp.find("vflip") != std::string::npos)
			vflip = true;
	}

	inline void MediaWidget::playmode(Int& data) const
	{
		static std::string temp;
		temp.clear();

		Property::Acquire(Handle, "loop-file", temp);

		if (temp == "no" || temp.empty())
			data = 0ULL;
		else
			data = 1ULL;
	}

	// =========================================================================================

	inline void MediaWidget::importPlaylist(const std::vector<QString>& data) const noexcept
	{
		for (auto& it : data) Command::Sync(Handle, { "loadfile", it.toStdString(), "append" });
	}
}
