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
		namespace event
		{
			class StartFileEvent
			{
			public:
				long long EntryID = -1;	//For playlist
			public:
				inline StartFileEvent& assign(const StartFileEvent& right);
				inline StartFileEvent& assign(const mpv_event_start_file& right);
			public:
				inline StartFileEvent() {};

				inline StartFileEvent(const StartFileEvent& right) { this->assign(right); }
				inline StartFileEvent(const mpv_event_start_file& right) { this->assign(right); }

				inline StartFileEvent& operator=(const StartFileEvent& right) { return this->assign(right); }
				inline StartFileEvent& operator=(const mpv_event_start_file& right) { return this->assign(right); }
			};

			inline StartFileEvent& StartFileEvent::assign(
				const StartFileEvent& right)
			{
				if (&right == this) return *this;
				this->EntryID = right.EntryID;

				return *this;
			}

			inline StartFileEvent& StartFileEvent::assign(
				const mpv_event_start_file& right)
			{
				this->EntryID = right.playlist_entry_id;
				return *this;
			}
		}
	}
}