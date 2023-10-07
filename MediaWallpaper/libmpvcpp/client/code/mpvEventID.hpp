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
		enum class EventID
		{
			None				= MPV_EVENT_NONE,
			Shutdown			= MPV_EVENT_SHUTDOWN,
			LogMessage			= MPV_EVENT_LOG_MESSAGE,
			GetProperty			= MPV_EVENT_GET_PROPERTY_REPLY,
			SetProperty			= MPV_EVENT_SET_PROPERTY_REPLY,
			CommandReply		= MPV_EVENT_COMMAND_REPLY,

			StartFile			= MPV_EVENT_START_FILE,
			EndFile				= MPV_EVENT_END_FILE,
			FileLoaded			= MPV_EVENT_FILE_LOADED,
			ClientMessage		= MPV_EVENT_CLIENT_MESSAGE,
			VideoReconfig		= MPV_EVENT_VIDEO_RECONFIG,
			AudioReconfig		= MPV_EVENT_AUDIO_RECONFIG,

			Seek				= MPV_EVENT_SEEK,
			PlaybackRestart		= MPV_EVENT_PLAYBACK_RESTART,
			PropertyChanged		= MPV_EVENT_PROPERTY_CHANGE,
			QueueOverflow		= MPV_EVENT_QUEUE_OVERFLOW,
			Hook				= MPV_EVENT_HOOK
		};

		inline EventID ToEventID(int value)
		{
			return static_cast<EventID>(value);
		}

		inline mpv_event_id FromEventID(const EventID& value)
		{
			return static_cast<mpv_event_id>(value);
		}

		inline std::string EventDescription(const EventID& value)
		{
			return mpv_event_name(FromEventID(value));
		}

		inline std::ostream& operator<<(std::ostream& out, const EventID& value)
		{
			out << static_cast<int>(value);
			return out;
		}
	}
}