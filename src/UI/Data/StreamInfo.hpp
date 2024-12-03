#pragma once
#include<QString>

namespace UI
{
	class StreamInfo
	{
	public:
		inline StreamInfo(StreamInfo&& right) noexcept;
		inline StreamInfo(const StreamInfo& right);
		inline StreamInfo() { this->clear(); }

		inline StreamInfo& operator=(StreamInfo&& right) noexcept;
		inline StreamInfo& operator=(const StreamInfo& right);

		int MonitorID = 0;
		inline void clear();
		inline virtual ~StreamInfo() {}
	public:
		QString Directory;
		QString Name;

		long long AtFullscreen;
		long long Playmode;
		long long AtFocus;
		long long Index;

		double Duration;
		double Position;
		double Volume;
		double Speed;

		bool Subtitle;
		bool Pause;
		bool Mute;

		struct Display
		{
			long long Brightness;
			long long Saturation;
			long long Contrast;

			long long Rotate;
			long long Gamma;
			long long Hue;

			double AspectRatio;
			double Panscan;
			double HAlign;
			double VAlign;

			bool HFlip;
			bool VFlip;
		public:
			inline void clear()
			{
				Brightness = 0;
				Saturation = 0;
				Contrast = 0;
				Rotate = 0;
				Gamma = 0;
				Hue = 0;

				AspectRatio = -1.0;
				Panscan = 0.0;
				HAlign = 0.0;
				VAlign = 0.0;

				HFlip = false;
				VFlip = false;
			}
		}
		Display;
	};

	inline StreamInfo::StreamInfo(StreamInfo&& right) noexcept
	{
		this->operator=(std::move(right));
	}

	inline StreamInfo::StreamInfo(const StreamInfo& right)
	{
		this->operator=(right);
	}

	inline StreamInfo& StreamInfo::operator=(StreamInfo&& right) noexcept
	{ /*Multi-monitor test: no this.MonitorID*/
		if (&right == this) return *this;

		Directory = std::move(right.Directory);
		Name = std::move(right.Name);

		AtFullscreen = right.AtFullscreen;
		Playmode = right.Playmode;
		AtFocus = right.AtFocus;
		Index = right.Index;

		Duration = right.Duration;
		Position = right.Position;
		Volume = right.Volume;
		Speed = right.Speed;

		Subtitle = right.Subtitle;
		Pause = right.Pause;
		Mute = right.Mute;

		Display = right.Display;
		right.clear();

		return *this;
	}

	inline StreamInfo& StreamInfo::operator=(const StreamInfo& right)
	{ /*Multi-monitor test: no this.MonitorID*/
		if (&right == this) return *this;

		Directory = right.Directory;
		Name = right.Name;

		AtFullscreen = right.AtFullscreen;
		Playmode = right.Playmode;
		AtFocus = right.AtFocus;
		Index = right.Index;

		Duration = right.Duration;
		Position = right.Position;
		Volume = right.Volume;
		Speed = right.Speed;

		Subtitle = right.Subtitle;
		Pause = right.Pause;
		Mute = right.Mute;

		Display = right.Display;
		return *this;
	}

	inline void StreamInfo::clear()
	{
		Directory.clear();
		Display.clear();
		Name.clear();

		AtFullscreen = 0;
		Playmode = 0;
		AtFocus = 0;
		Index = -1;

		Duration = 0.0;
		Position = 0.0;
		Volume = 100.0;
		Speed = 1.0;

		Subtitle = true;
		Pause = false;
		Mute = false;
	}
}
