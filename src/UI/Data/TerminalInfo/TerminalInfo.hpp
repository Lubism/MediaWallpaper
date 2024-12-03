#pragma once
#include"UI/Data/StartupInfo.hpp"
#include"UI/Data/JsonIO.hpp"

#include<QRect>

namespace UI
{
	class TerminalInfo
	{
	public:
		static inline void ImportRect(const QRect& rect);
		static inline void LaunchStartup();
		static inline void Write();
		static inline void Read();
	public:
		static QString Lang;
		static QString Font;
		static bool Startup;

		static int Fontsize;
		static int Height;
		static int Width;
	private:
		static const QString Path;
		static JsonIO::Map Map;
	private:
		inline TerminalInfo() = delete;
		inline ~TerminalInfo() = delete;
	};

	inline void TerminalInfo::ImportRect(const QRect& rect)
	{
		Height = rect.height();
		Width = rect.width();
	}

	inline void TerminalInfo::LaunchStartup()
	{
		if (TerminalInfo::Startup)
			StartupInfo::CreateMark();
		else
			StartupInfo::DeleteMark();
	}

	inline void TerminalInfo::Write()
	{
		auto& mainWindow = Map["MainWindow"];
		mainWindow["Height"] = Height;
		mainWindow["Width"] = Width;

		auto& terminal = Map["Terminal"];

		terminal["Lang"] = Lang.toStdString();
		terminal["Font"] = Font.toStdString();
		terminal["Fontsize"] = Fontsize;
		terminal["Startup"] = Startup;

		JsonIO::Write(Path, Map);
	}

	inline void TerminalInfo::Read()
	{
		JsonIO::Read(Path, Map);

		auto& mainWindow = Map["MainWindow"];

		JsonIO::GetValue(mainWindow, "Height", Height);
		JsonIO::GetValue(mainWindow, "Width", Width);

		auto& terminal = Map["Terminal"];

		JsonIO::GetValue(terminal, "Lang", Lang);
		JsonIO::GetValue(terminal, "Font", Font);

		JsonIO::GetValue(terminal, "Fontsize", Fontsize);
		JsonIO::GetValue(terminal, "Startup", Startup);
	}
}
