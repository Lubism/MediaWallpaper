#pragma once
#include"client/container/mpvNode.hpp"

namespace mpv
{
	namespace client
	{
		namespace event
		{
			class CommandEvent
			{
			public:
				client::Node Node;
			public:
				inline CommandEvent& assign(const CommandEvent& right);
				inline CommandEvent& assign(const mpv_event_command& right);
			public:
				inline CommandEvent() {};

				inline CommandEvent(const CommandEvent& right) { this->assign(right); }
				inline CommandEvent(const mpv_event_command& right) { this->assign(right); }

				inline CommandEvent& operator=(const CommandEvent& right) { return this->assign(right); }
				inline CommandEvent& operator=(const mpv_event_command& right) { return this->assign(right); }
			};

			inline CommandEvent& CommandEvent::assign(const CommandEvent& right)
			{
				if (&right == this) return *this;
				this->Node = right.Node;
				return *this;
			}

			inline CommandEvent& CommandEvent::assign(const mpv_event_command& right)
			{
				this->Node = right.result;
				return *this;
			}
		}
	}
}