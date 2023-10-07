#pragma once
#include"client/eventcategories/mpvStartFileEvent.hpp"
#include"client/eventcategories/mpvPropertyEvent.hpp"
#include"client/eventcategories/mpvCommandEvent.hpp"
#include"client/eventcategories/mpvEndFileEvent.hpp"
#include"client/eventcategories/mpvClientEvent.hpp"
#include"client/eventcategories/mpvHookEvent.hpp"
#include"client/eventcategories/mpvLogEvent.hpp"
#include"client/code/mpvEventID.hpp"
#include"client/mpvHandle.hpp"

namespace mpv
{
	namespace client
	{
		class Event
		{
		public:
			event::StartFileEvent StartFileEvent;
			event::PropertyEvent PropertyEvent;
			event::CommandEvent CommandEvent;
			event::EndFileEvent EndFileEvent;
			event::ClientEvent ClientEvent;
			event::HookEvent HookEvent;
			event::LogEvent LogEvent;
		public:
			unsigned long long ReplyData = 0;
			Error ErrorCode = Error::Generic;
			EventID ID = EventID::None;
		public:
			inline void receive(const Handle& handle,
				double timeout,
				Node& result);

			inline void receive(const Handle& handle,
				double timeout);
		public:
			inline Event() {}
			inline Event(const Event& right) { this->assign(right); }
			inline Event& operator=(const Event& right) { this->assign(right); }
		private:
			inline Event& assign(const Event& right);
			void assign(const mpv_event& right);
		};

		inline void Event::receive(const Handle& handle,
			double timeout, Node& result)
		{
			if (!handle || (timeout < 0.0))
			{
				throw Exception(this, Error::InvalidParameter);
			}

			mpv_event data = *mpv_wait_event(
				handle.Data, timeout);
			mpv_node node{};

			Error error = ToError(mpv_event_to_node(&node, &data));
			if (error != Error::Success)
			{
				throw Exception(this, error);
			}

			result = node;
			this->assign(data);
			mpv_free_node_contents(&node);
		}

		inline void Event::receive(const Handle& handle,
			double timeout)
		{
			if (!handle || (timeout < 0.0))
			{
				throw Exception(this, Error::InvalidParameter);
			}

			mpv_event data = *mpv_wait_event(
				handle.Data, timeout);
			this->assign(data);
		}

		inline Event& Event::assign(const Event& right)
		{
			if (&right == this) return *this;

			this->StartFileEvent = right.StartFileEvent;
			this->PropertyEvent = right.PropertyEvent;
			this->CommandEvent = right.CommandEvent;
			this->EndFileEvent = right.EndFileEvent;
			this->ClientEvent = right.ClientEvent;
			this->HookEvent = right.HookEvent;
			this->LogEvent = right.LogEvent;

			this->ReplyData = right.ReplyData;
			this->ErrorCode = right.ErrorCode;
			this->ID = right.ID;

			return *this;
		}
	}
}