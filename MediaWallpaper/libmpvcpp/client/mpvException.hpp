#pragma once
#include<exception>
#include<sstream>
#include<string>

#include"code/mpvError.hpp"

namespace mpv
{
	namespace client
	{
		class Exception :public std::exception
		{
		public:
			inline Exception(const void* value = nullptr, const std::string& description = "Unknown exception")
				:exception()
			{
				this->Converter << value;
				std::string address = "";

				this->Converter >> address;
				this->writeAddress(address);

				this->Description = description;
				this->writeMessage();
			}

			inline Exception(const void* value = nullptr, const Error& error = Error::Generic,
				const std::string& name = "no name")
				:exception()
			{
				this->Converter << value;
				std::string address = "";

				this->Converter >> address;
				this->writeAddress(address);

				std::string copyname = name;

				copyname.empty() ? (copyname.assign("no name")) : copyname;
				this->Description = "(" + copyname + ")";

				this->Description += ErrorDescription(error);
				this->writeMessage();
			}

			inline char const* what() const override
			{
				return this->Message.c_str();
			}
		private:
			inline void writeAddress(const std::string& address)
			{
				this->Address = "[@" + address + "]";
			}

			inline void writeMessage()
			{
				this->Description[0] = std::toupper(this->Description[0]);
				this->Message = this->Address + this->Description + "\n";
			}
		private:
			std::stringstream Converter;
			std::string Description;
			std::string Address;
			std::string Message;
		};
	}
}