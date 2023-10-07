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
		enum class Format
		{
			None		= MPV_FORMAT_NONE,
			String		= MPV_FORMAT_STRING,
			OSDString	= MPV_FORMAT_OSD_STRING,

			BooleanInt	= MPV_FORMAT_FLAG,
			Int			= MPV_FORMAT_INT64,
			Double		= MPV_FORMAT_DOUBLE,

			Node		= MPV_FORMAT_NODE,
			NodeArray	= MPV_FORMAT_NODE_ARRAY,
			NodeMap		= MPV_FORMAT_NODE_MAP,

			ByteArray	= MPV_FORMAT_BYTE_ARRAY
		};

		inline Format ToFormat(int value)
		{
			return static_cast<Format>(value);
		}

		inline mpv_format FromFormat(const Format& value)
		{
			return static_cast<mpv_format>(value);
		}

		inline std::ostream& operator<<(std::ostream& out, const Format& value)
		{
			out << static_cast<int>(value);
			return out;
		}
	}
}