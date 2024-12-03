#pragma once
#include<QApplication>
#include<QSettings>
#include<QString>
#include<QFile>

#include<memory>
#include<vector>

namespace UI
{

#ifdef _WIN32

	class StartupInfo
	{
	public:
		static inline void CreateMark();
		static inline bool DeleteMark();
	private:
		static inline void SetRegedit(bool state);
	private:
		inline StartupInfo() = delete;
		inline ~StartupInfo() = delete;
	};

	inline void StartupInfo::CreateMark()
	{
		auto name = QApplication::applicationName();
		QString cmd(1 << 8, '\0');
		cmd.clear();

		static const std::vector<QString> bat =
		{
			"@echo off",
			"\n",

			"cd /d %~dp0",
			"\n",

			"start \"\" \"" + name + ".exe\"",
			"\n",

			"exit"
		};
		for (auto& it : bat) cmd.append(it);

		QFile file(name + QString(".bat"));
		file.open(QIODevice::WriteOnly | QIODevice::Truncate);

		file.write(cmd.toLocal8Bit());
		file.close();

		StartupInfo::SetRegedit(true);
	}

	inline bool StartupInfo::DeleteMark()
	{
		auto name = QApplication::applicationName() + ".bat";
		auto temp = name.toStdString();

		int ret = std::remove(temp.c_str());
		StartupInfo::SetRegedit(false);
		return (!ret ? true : false);
	}

	inline void StartupInfo::SetRegedit(bool state)
	{
		const QString regPath = "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
		std::unique_ptr<QSettings>  ptr(new QSettings(regPath, QSettings::NativeFormat));
		QString prefix = "\"" + QApplication::applicationDirPath().replace("/", "\\");
		QString suffix = "\\" + QApplication::applicationName() + ".bat\"";
		QString name = QApplication::applicationName();

		if (state)
			ptr->setValue(name, prefix + suffix);
		else
			ptr->remove(name);
	}

#endif // _WIN32

#ifdef __linux__

	class StartupInfo
	{
	private:
		inline StartupInfo() = delete;
		inline ~StartupInfo() = delete;
	};

#endif // __linux__

}
