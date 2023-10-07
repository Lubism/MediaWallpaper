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
		enum class EndFileReason
		{
			None					= -1,
			EndOfFile				= MPV_END_FILE_REASON_EOF,
			Stopped					= MPV_END_FILE_REASON_STOP,
			Quit					= MPV_END_FILE_REASON_QUIT,
			Error					= MPV_END_FILE_REASON_ERROR,
			Redirection				= MPV_END_FILE_REASON_REDIRECT
		};

		inline EndFileReason ToEndFileReason(int value)
		{
			return static_cast<EndFileReason>(value);
		}

		inline mpv_end_file_reason FromEndFileReason(const EndFileReason& value)
		{
			return static_cast<mpv_end_file_reason>(value);
		}

		inline std::ostream& operator<<(std::ostream& out, const EndFileReason& value)
		{
			out << static_cast<int>(value);
			return out;
		}
	}
}