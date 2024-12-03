#pragma once
#include"UI/Data/StreamInfo.hpp"
#include"UI/Data/JsonIO.hpp"

namespace UI
{
	class ScreenInfo
	{
	public:
		static inline void ExportInfo(StreamInfo& ret, int screenIndex);
		static inline void ImportInfo(const StreamInfo& info);
		static inline void Write();
		static inline void Read();
	private:
		inline ScreenInfo() = delete;
		inline ~ScreenInfo() = delete;
	private:
		static const QString Path;
		static JsonIO::Map Map;
	};

	inline void ScreenInfo::ExportInfo(StreamInfo& ret, int screenIndex)
	{
		auto name = "Monitor#" + std::to_string(screenIndex);
		auto& map = Map[name];

		JsonIO::GetValue(map, "Directory", ret.Directory);
		JsonIO::GetValue(map, "Name", ret.Name);

		JsonIO::GetValue(map, "Playmode", ret.Playmode);
		JsonIO::GetValue(map, "Index", ret.Index);

		JsonIO::GetValue(map, "Position", ret.Position);
		JsonIO::GetValue(map, "Volume", ret.Volume);
		JsonIO::GetValue(map, "Speed", ret.Speed);

		JsonIO::GetValue(map, "Subtitle", ret.Subtitle);
		JsonIO::GetValue(map, "Pause", ret.Pause);
		JsonIO::GetValue(map, "Mute", ret.Mute);
	}

	inline void ScreenInfo::ImportInfo(const StreamInfo& info)
	{
		auto name = "Monitor#" + std::to_string(info.MonitorID);
		auto& map = Map[name];

		map["Directory"] = info.Directory.toStdString();
		map["Playmode"] = info.Playmode;

		map["Name"] = info.Name.toStdString();
		map["Index"] = info.Index;

		map["Position"] = info.Position;
		map["Volume"] = info.Volume;
		map["Speed"] = info.Speed;

		map["Subtitle"] = info.Subtitle;
		map["Pause"] = info.Pause;
		map["Mute"] = info.Mute;
	}

	inline void ScreenInfo::Write()
	{
		JsonIO::Write(Path, Map);
	}

	inline void ScreenInfo::Read()
	{
		JsonIO::Read(Path, Map);
	}
}
