#pragma once
#include<ostream>

extern "C"
{
#include<mpv/client.h>
}

namespace mpv
{
	namespace client
	{
		enum class LogLevel
		{
			None	= MPV_LOG_LEVEL_NONE,
			Fatal	= MPV_LOG_LEVEL_FATAL,
			Error	= MPV_LOG_LEVEL_ERROR,

			Warn	= MPV_LOG_LEVEL_WARN,
			Info	= MPV_LOG_LEVEL_INFO,
			V		= MPV_LOG_LEVEL_V,

			Debug	= MPV_LOG_LEVEL_DEBUG,
			Trace	= MPV_LOG_LEVEL_TRACE
		};

		inline LogLevel ToLogLevel(int value)
		{
			return static_cast<LogLevel>(value);
		}

		inline mpv_log_level FromLogLevel(const LogLevel& value)
		{
			return static_cast<mpv_log_level>(value);
		}

		inline std::ostream& operator<<(std::ostream& out, const LogLevel& value)
		{
			out << static_cast<int>(value);
			return out;
		}
	}
}