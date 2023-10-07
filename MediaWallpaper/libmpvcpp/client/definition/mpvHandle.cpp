#include"client/mpvHandle.hpp"

using namespace mpv::client;

void Handle::setLogRequest(const LogLevel& minLogLevel) const
{
	this->isCreated();
	std::string arg = "";
	switch (minLogLevel)
	{
	case LogLevel::None:
		arg = "no";
		break;
	case LogLevel::Fatal:
		arg = "fatal";
		break;
	case LogLevel::Error:
		arg = "error";
		break;
	case LogLevel::Warn:
		arg = "warn";
		break;
	case LogLevel::Info:
		arg = "info";
		break;
	case LogLevel::V:
		arg = "v";
		break;
	case LogLevel::Debug:
		arg = "debug";
		break;
	case LogLevel::Trace:
		arg = "trace";
		break;
	}
	Error error = ToError(mpv_request_log_messages(
		this->Data, arg.data()));
	this->validationSuccess(error);
}