#pragma once
#include"client/mpvException.hpp"

#include<vector>

namespace mpv
{
	namespace client
	{
		namespace event
		{
			class ClientEvent
			{
			public:
				std::vector<std::string> Args;
			public:
				inline ClientEvent& assign(const ClientEvent& right);
				inline ClientEvent& assign(const mpv_event_client_message& right);
			public:
				inline ClientEvent() {};

				inline ClientEvent(const ClientEvent& right) { this->assign(right); }
				inline ClientEvent(const mpv_event_client_message& right) { this->assign(right); }

				inline ClientEvent& operator=(const ClientEvent& right) { return this->assign(right); }
				inline ClientEvent& operator=(const mpv_event_client_message& right) { return this->assign(right); }
			};

			inline ClientEvent& ClientEvent::assign(const ClientEvent& right)
			{
				if (&right == this) return *this;

				Args.assign(right.Args.begin(),
					right.Args.end());

				return *this;
			}

			inline ClientEvent& ClientEvent::assign(const mpv_event_client_message& right)
			{
				if (right.num_args == 0 || right.args == nullptr)
				{
					throw Exception(this, Error::InvalidParameter);
					return *this;
				}

				for (int it = 0; it < right.num_args; it++)
					Args.push_back(right.args[it]);

				return *this;
			}
		}
	}
}