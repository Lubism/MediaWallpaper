#pragma once
#include"UI/Data/StreamInfo.hpp"
#include"UI/Data/JsonIO.hpp"

namespace UI
{
	class DisplayInfo
	{
	public:
		static inline void ExportInfo(StreamInfo& ret, int screenIndex);
		static inline void ImportInfo(const StreamInfo& info);
		static inline void Write();
		static inline void Read();
	private:
		inline DisplayInfo() = delete;
		inline ~DisplayInfo() = delete;
	private:
		static const QString Path;
		static JsonIO::Map Map;
	};

	inline void DisplayInfo::ExportInfo(StreamInfo& ret, int screenIndex)
	{
		auto name = "Monitor#" + std::to_string(screenIndex);
		auto& ref = ret.Display;
		auto& map = Map[name];

		JsonIO::GetValue(map, "Brightness", ref.Brightness);
		JsonIO::GetValue(map, "Saturation", ref.Saturation);
		JsonIO::GetValue(map, "Contrast", ref.Contrast);
		JsonIO::GetValue(map, "Rotate", ref.Rotate);
		JsonIO::GetValue(map, "Gamma", ref.Gamma);
		JsonIO::GetValue(map, "Hue", ref.Hue);

		JsonIO::GetValue(map, "AspectRatio", ref.AspectRatio);
		JsonIO::GetValue(map, "Panscan", ref.Panscan);
		JsonIO::GetValue(map, "HAlign", ref.HAlign);
		JsonIO::GetValue(map, "VAlign", ref.VAlign);

		JsonIO::GetValue(map, "HFlip", ref.HFlip);
		JsonIO::GetValue(map, "VFlip", ref.VFlip);
	}

	inline void DisplayInfo::ImportInfo(const StreamInfo& info)
	{
		auto name = "Monitor#" + std::to_string(info.MonitorID);
		auto& ref = info.Display;
		auto& map = Map[name];

		map["Brightness"] = ref.Brightness;
		map["Saturation"] = ref.Saturation;
		map["Contrast"] = ref.Contrast;
		map["Rotate"] = ref.Rotate;
		map["Gamma"] = ref.Gamma;
		map["Hue"] = ref.Hue;

		map["AspectRatio"] = ref.AspectRatio;
		map["Panscan"] = ref.Panscan;
		map["HAlign"] = ref.HAlign;
		map["VAlign"] = ref.VAlign;

		map["HFlip"] = ref.HFlip;
		map["VFlip"] = ref.VFlip;
	}

	inline void DisplayInfo::Write()
	{
		JsonIO::Write(Path, Map);
	}

	inline void DisplayInfo::Read()
	{
		JsonIO::Read(Path, Map);
	}
}
