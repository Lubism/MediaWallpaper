#include"client/container/mpvEvent.hpp"

using namespace mpv::client;

void Event::assign(const mpv_event& right)
{
	this->ID = ToEventID(right.event_id);

	switch (this->ID)
	{
	case EventID::PropertyChanged:
		this->ReplyData = right.reply_userdata;
		this->PropertyEvent = *static_cast<mpv_event_property*>(right.data);
		break;
	case EventID::ClientMessage:
		this->ClientEvent = *static_cast<mpv_event_client_message*>(right.data);
		break;
	case EventID::CommandReply:
		this->ErrorCode = ToError(right.error);
		this->ReplyData = right.reply_userdata;
		this->CommandEvent = *static_cast<mpv_event_command*>(right.data);
		break;
	case EventID::GetProperty:
		this->ErrorCode = ToError(right.error);
		this->ReplyData = right.reply_userdata;
		this->PropertyEvent = *static_cast<mpv_event_property*>(right.data);
		break;
	case EventID::SetProperty:
		this->ErrorCode = ToError(right.error);
		this->ReplyData = right.reply_userdata;
		break;
	case EventID::LogMessage:
		this->LogEvent = *static_cast<mpv_event_log_message*>(right.data);
		break;
	case EventID::StartFile:
		this->StartFileEvent = *static_cast<mpv_event_start_file*>(right.data);
		break;
	case EventID::EndFile:
		this->EndFileEvent = *static_cast<mpv_event_end_file*>(right.data);
		break;
	case EventID::Hook:
		this->ReplyData = right.reply_userdata;
		this->HookEvent = *static_cast<mpv_event_hook*>(right.data);
		break;
	}
}