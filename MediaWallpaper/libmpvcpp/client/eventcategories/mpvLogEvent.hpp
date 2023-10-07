#pragma once
#include"client/code/mpvLogLevel.hpp"
#include"client/mpvException.hpp"

namespace mpv
{
	namespace client
	{
		namespace event
		{
			class LogEvent
			{
			public:
				std::string LevelDescription = "";
				LogLevel Level = LogLevel::None;
				std::string Prefix = "";
				std::string Text = "";
			public:
				inline LogEvent& assign(const LogEvent& right);
				inline LogEvent& assign(const mpv_event_log_message& right);
			public:
				inline LogEvent() {};

				inline LogEvent(const LogEvent& right) { this->assign(right); }
				inline LogEvent(const mpv_event_log_message& right) { this->assign(right); }

				inline LogEvent& operator=(const LogEvent& right) { return this->assign(right); }
				inline LogEvent& operator=(const mpv_event_log_message& right) { return this->assign(right); }
			};

			inline LogEvent& LogEvent::assign(const LogEvent& right)
			{
				if (&right == this) return *this;

				this->LevelDescription = right.LevelDescription;
				this->Prefix = right.Prefix;
				this->Level = right.Level;
				this->Text = right.Text;

				return *this;
			}

			inline LogEvent& LogEvent::assign(const mpv_event_log_message& right)
			{
				if (!right.prefix || !right.level || !right.text)
				{
					throw Exception(this, Error::InvalidParameter);
					return *this;
				}

				this->Level = ToLogLevel(right.log_level);
				this->LevelDescription = right.level;
				this->Prefix = right.prefix;
				this->Text = right.text;
				return *this;
			}
		}
	}
}