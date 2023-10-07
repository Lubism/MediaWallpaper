#pragma once
#include"client/code/mpvEndFileReason.hpp"
#include"client/code/mpvError.hpp"

namespace mpv
{
	namespace client
	{
		namespace event
		{
			class EndFileEvent
			{
			public:
				EndFileReason Reason = EndFileReason::None;
				Error ErrorCode = Error::Generic;

				long long EntryID = -1;		//For playlist
				long long InsertID = -1;	//For playlist
				int InsertNumEntries = -1;	//For playlist
			public:
				inline EndFileEvent& assign(const EndFileEvent& right);
				inline EndFileEvent& assign(const mpv_event_end_file& right);
			public:
				inline EndFileEvent() {};

				inline EndFileEvent(const EndFileEvent& right) { this->assign(right); }
				inline EndFileEvent(const mpv_event_end_file& right) { this->assign(right); }

				inline EndFileEvent& operator=(const EndFileEvent& right) { return this->assign(right); }
				inline EndFileEvent& operator=(const mpv_event_end_file& right) { return this->assign(right); }
			};

			inline EndFileEvent& EndFileEvent::assign(
				const EndFileEvent& right)
			{
				if (&right == this) return *this;

				this->InsertNumEntries = right.InsertNumEntries;
				this->ErrorCode = right.ErrorCode;
				this->InsertID = right.InsertID;
				this->EntryID = right.EntryID;
				this->Reason = right.Reason;

				return *this;
			}

			inline EndFileEvent& EndFileEvent::assign(
				const mpv_event_end_file& right)
			{
				this->InsertNumEntries = right.playlist_insert_num_entries;
				this->Reason = ToEndFileReason(right.reason);
				this->InsertID = right.playlist_insert_id;
				this->EntryID = right.playlist_entry_id;
				this->ErrorCode = ToError(right.error);

				return *this;
			}
		}
	}
}