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
		enum class Error
		{
			Success					= MPV_ERROR_SUCCESS,
			EventQueueFull			= MPV_ERROR_EVENT_QUEUE_FULL,
			NoMemory				= MPV_ERROR_NOMEM,
			Uninitialized			= MPV_ERROR_UNINITIALIZED,
			InvalidParameter		= MPV_ERROR_INVALID_PARAMETER,

			InexistentProperty		= MPV_ERROR_PROPERTY_NOT_FOUND,
			InvalidPropertyFormat	= MPV_ERROR_PROPERTY_FORMAT,
			UnattachableProperty	= MPV_ERROR_PROPERTY_UNAVAILABLE,
			Property				= MPV_ERROR_PROPERTY_ERROR,

			Command					= MPV_ERROR_COMMAND,
			LoadFailed				= MPV_ERROR_LOADING_FAILED,
			AudioOutputInit			= MPV_ERROR_AO_INIT_FAILED,
			VideoOutputInit			= MPV_ERROR_VO_INIT_FAILED,
			EmptyContext			= MPV_ERROR_NOTHING_TO_PLAY,

			UnknownFormat			= MPV_ERROR_UNKNOWN_FORMAT,
			Unsupported				= MPV_ERROR_UNSUPPORTED,
			Unimplemented			= MPV_ERROR_NOT_IMPLEMENTED,
			Generic					= MPV_ERROR_GENERIC
		};

		inline Error ToError(int value)
		{
			return static_cast<Error>(value);
		}

		inline mpv_error FromError(const Error& value)
		{
			return static_cast<mpv_error>(value);
		}

		inline std::string ErrorDescription(Error value)
		{
			return mpv_error_string(FromError(value));
		}

		inline std::ostream& operator<<(std::ostream& out, const Error& value)
		{
			out << static_cast<int>(value);
			return out;
		}
	}
}