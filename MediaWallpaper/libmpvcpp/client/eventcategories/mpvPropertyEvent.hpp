#pragma once
#include"client/container/mpvNode.hpp"
#include"client/mpvException.hpp"

namespace mpv
{
	namespace client
	{
		namespace event
		{
			class PropertyEvent
			{
			public:
				std::string Name = "";
				Format FormatType = Format::None;

				std::string String = "";
				double Double = 0.0;
				long long Int = 0;
				bool Bool = false;
				client::Node Node;
			public:
				inline PropertyEvent& assign(const PropertyEvent& right);
				inline PropertyEvent& assign(const mpv_event_property& right);
			public:
				inline PropertyEvent() {};

				inline PropertyEvent(const PropertyEvent& right) { this->assign(right); }
				inline PropertyEvent(const mpv_event_property& right) { this->assign(right); }

				inline PropertyEvent& operator=(const PropertyEvent& right) { return this->assign(right); }
				inline PropertyEvent& operator=(const mpv_event_property& right) { return this->assign(right); }
			};

			inline PropertyEvent& PropertyEvent::assign(const PropertyEvent& right)
			{
				if (&right == this) return *this;

				this->FormatType = right.FormatType;
				this->String = right.String;
				this->Double = right.Double;
				this->Name = right.Name;
				this->Node = right.Node;
				this->Bool = right.Bool;
				this->Int = right.Int;

				return *this;
			}

			inline PropertyEvent& PropertyEvent::assign(const mpv_event_property& right)
			{
				if (right.data == nullptr)
				{
					throw Exception(this, Error::InvalidParameter);
					return *this;
				}

				int flag = 0;
				this->Name = right.name;
				this->FormatType = ToFormat(right.format);
				switch (this->FormatType)
				{
				case Format::BooleanInt:
					flag = *static_cast<int*>(right.data);
					this->Bool = ((flag == 1) ? true : false);
					break;
				case Format::String:
					this->String = static_cast<const char*>(right.data);
					break;
				case Format::Double:
					this->Double = *static_cast<double*>(right.data);
					break;
				case Format::Node:
					this->Node = *static_cast<mpv_node*>(right.data);
					break;
				case Format::Int:
					this->Int = *static_cast<long long*>(right.data);
					break;
				default:
					break;
				}

				return *this;
			}
		}
	}
}