#pragma once
#include"client/mpvException.hpp"

namespace mpv
{
	namespace client
	{
		namespace event
		{
			class HookEvent
			{
			public:
				unsigned long long ID = 0;
				std::string Name = "";
			public:
				inline HookEvent& assign(const HookEvent& right);
				inline HookEvent& assign(const mpv_event_hook& right);
			public:
				inline HookEvent() {};

				inline HookEvent(const HookEvent& right) { this->assign(right); }
				inline HookEvent(const mpv_event_hook& right) { this->assign(right); }

				inline HookEvent& operator=(const HookEvent& right) { return this->assign(right); }
				inline HookEvent& operator=(const mpv_event_hook& right) { return this->assign(right); }
			};

			inline HookEvent& HookEvent::assign(const HookEvent& right)
			{
				if (&right == this) return *this;
				this->Name = right.Name;
				this->ID = right.ID;
				return *this;
			}

			inline HookEvent& HookEvent::assign(const mpv_event_hook& right)
			{
				if (right.name == nullptr)
				{
					throw Exception(this, Error::InvalidParameter);
					return *this;
				}

				this->Name = right.name;
				this->ID = right.id;

				return *this;
			}
		}
	}
}