#pragma once
#include"code/mpvLogLevel.hpp"
#include"code/mpvEventID.hpp"
#include"mpvException.hpp"

namespace mpv
{
	namespace client
	{
		class Handle
		{
			using wide = long long;
			using uint = unsigned long long;
		public:
			inline Handle() {}
			inline ~Handle() { this->destroy(); }
			inline Handle(const Handle&) = delete;
			inline Handle& operator=(const Handle&) = delete;
			inline bool operator!() const { return !this->createState; }

			inline void create();
			inline void create(const Handle& handle, const std::string& name);
			inline void weakCreate(const Handle& handle, const std::string& name);

			inline void initialize();
			inline wide clientID() const;
			inline wide internalTime() const;
			inline std::string clientName() const;
			inline void loadConfig(const std::string& filePath) const;

			void setLogRequest(const LogLevel& minLogLevel) const;
			inline void setEventRequest(const EventID& eventID,
				bool enableReceiving = true) const;
			inline void waitAsyncRequests() const;

			template<typename Func, typename Arg>
			inline void setWakeupCallback(Func func, Arg& arg) const;
			inline void wakeup() const;

			inline void continueHook(uint replyData) const;
			inline void addHook(uint replyData,
				const std::string& name,
				int priority) const;

			inline void destroy();
			inline void terminate();
		private:
			inline void validationSuccess(const Error& error) const;
			inline void isCreated(bool checkCreated = true) const;
			inline void isInitialized() const;
			inline void clearState();
		private:
			mpv_handle* Data = nullptr;
			bool createState = false;
			bool initState = false;
			friend class Property;
			friend class Command;
			friend class Event;
		};

		inline void Handle::create()
		{
			this->isCreated(false);
			this->Data = mpv_create();
			if (this->Data == nullptr) this->validationSuccess(
				Error::NoMemory);
			this->createState = true;
		}

		inline void Handle::create(const Handle& handle,
			const std::string& name)
		{
			this->isCreated(false);
			handle.isCreated(false);
			this->Data = mpv_create_client(handle.Data, name.data());
			if (this->Data == nullptr) this->validationSuccess(
				Error::NoMemory);
			this->createState = true;
		}

		inline void Handle::weakCreate(const Handle& handle,
			const std::string& name)
		{
			this->isCreated(false);
			handle.isCreated(false);
			this->Data = mpv_create_weak_client(handle.Data, name.data());
			if (this->Data == nullptr) this->validationSuccess(
				Error::NoMemory);
			this->createState = true;
		}

		inline void Handle::initialize()
		{
			this->isCreated();
			this->isInitialized();
			Error error = ToError(mpv_initialize(
				this->Data));
			this->validationSuccess(error);
			this->initState = true;
		}

		inline Handle::wide Handle::clientID() const
		{
			this->isCreated();
			return mpv_client_id(this->Data);
		}

		inline Handle::wide Handle::internalTime() const
		{
			this->isCreated();
			return mpv_get_time_us(this->Data);
		}

		inline std::string Handle::clientName() const
		{
			this->isCreated();
			return mpv_client_name(this->Data);
		}

		inline void Handle::loadConfig(const std::string& filePath) const
		{
			this->isCreated();
			Error error = ToError(mpv_load_config_file(
				this->Data, filePath.data()));
			this->validationSuccess(error);
		}

		inline void Handle::setEventRequest(const EventID& eventID,
			bool enableReceiving) const
		{
			this->isCreated();
			int flag = enableReceiving ? 1 : 0;
			Error error = ToError(mpv_request_event(this->Data,
				FromEventID(eventID), flag));
			this->validationSuccess(error);
		}

		inline void Handle::waitAsyncRequests() const
		{
			this->isCreated();
			mpv_wait_async_requests(this->Data);
		}

		template<typename Func, typename Arg>
		inline void Handle::setWakeupCallback(
			Func func, Arg& arg) const
		{
			this->isCreated();
			auto callback = reinterpret_cast<void (*)(void*)>(func);
			mpv_set_wakeup_callback(this->Data, callback, &arg);
		}

		inline void Handle::wakeup() const
		{
			mpv_wakeup(this->Data);
		}

		inline void Handle::continueHook(uint replyData) const
		{
			this->isCreated();
			Error error = ToError(mpv_hook_continue(
				this->Data, replyData));
			this->validationSuccess(error);
		}

		inline void Handle::addHook(uint replyData,
			const std::string& name,
			int priority) const
		{
			this->isCreated();
		}

		inline void Handle::destroy()
		{
			mpv_destroy(this->Data);
			this->clearState();
		}

		inline void Handle::terminate()
		{
			mpv_terminate_destroy(this->Data);
			this->clearState();
		}

		inline void Handle::validationSuccess(
			const Error& error) const
		{
			if (error != Error::Success)
			{
				throw Exception(this, error, "handle");
			}
		}

		inline void Handle::isCreated(bool checkCreated) const
		{
			if (checkCreated)
			{
				if (this->createState == false) throw Exception(
					this, "Handle is not created !");
			}
			else
			{
				if (this->createState == true) throw Exception(
					this, "Handle has been created !");
			}
		}

		inline void Handle::isInitialized() const
		{
			if (this->initState == true) throw Exception(
				this, "Handle has been initialized"
			);
		}

		inline void Handle::clearState()
		{
			this->Data = nullptr;
			this->initState = false;
			this->createState = false;
		}
	}
}