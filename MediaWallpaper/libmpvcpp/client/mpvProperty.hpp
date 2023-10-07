#pragma once
#include"client/container/mpvNode.hpp"
#include"mpvHandle.hpp"

namespace mpv
{
	namespace client
	{
		class Property
		{
			using uint = unsigned long long;
		public:
			template<typename Ty>
			static inline void apply(const Handle& handle, const std::string& name,
				const Format& format, Ty data);

			static inline void apply(const Handle& handle, const std::string& name,
				const Format& format, bool data);

			static inline void apply(const Handle& handle, const std::string& name,
				const Format& format, Node data);

			static inline void apply(const Handle& handle, const std::string& name,
				const Format& format, const std::string& data);
		public:
			template<typename Ty>
			static inline void apply(const Handle& handle, const std::string& name,
				const Format& format, Ty data, const uint& replyData);

			static inline void apply(const Handle& handle, const std::string& name,
				const Format& format, bool data, const uint& replyData);

			static inline void apply(const Handle& handle, const std::string& name,
				const Format& format, Node data, const uint& replyData);

			static inline void apply(const Handle& handle, const std::string& name,
				const Format& format, const std::string& data,
				const uint& replyData);
		public:
			template<typename Ty>
			static inline void acquire(const Handle& handle, const std::string& name,
				const Format& format, Ty& data);

			static inline void acquire(const Handle& handle, const std::string& name,
				const Format& format, bool& data);

			static inline void acquire(const Handle& handle, const std::string& name,
				const Format& format, Node& data);

			static inline void acquire(const Handle& handle, const std::string& name,
				const Format& format, std::string& data);

			static inline void acquire(const Handle&, const std::string&,
				const Format&, const char*) = delete;

			static inline void asyncAcquire(const Handle& handle, const std::string& name,
				const Format& format, const uint& replyData);
		public:
			static inline void observe(const Handle& handle, const std::string& name,
				const Format& format, const uint& replyData);

			static inline void unobserve(const Handle& handle,
				const uint& replyData);

			static inline void remove(const Handle& handle,
				const std::string& name);
		protected:
			static inline void validationParam(const Handle& handle,
				const std::string& name);

			static inline void validationParam(const Handle& handle,
				const std::string& name, const Format& format,
				std::string data);

			static inline void validationParam(const Handle& handle,
				const std::string& name, const Format& format,
				ByteArray& data);

			static inline void validationParam(const Handle& handle,
				const std::string& name, const Format& format,
				long long data);

			static inline void validationParam(const Handle& handle,
				const std::string& name, const Format& format,
				double& data);

			static inline void validationParam(const Handle& handle,
				const std::string& name, const Format& format,
				Node& data);

			static inline void validationParam(const Handle& handle,
				const std::string& name, const Format& format,
				bool& data);

			static inline void validationSuccess(const Handle& handle,
				Error error, const std::string& name = "no name");
		};

		//========================================================================
		// apply property synchronously

		template<typename Ty>
		inline void Property::apply(const Handle& handle, const std::string& name,
			const Format& format, Ty data)
		{
			Property::validationParam(handle, name, format, data);
			Error error = ToError(mpv_set_property(handle.Data,
				name.data(), FromFormat(format), &data));
			Property::validationSuccess(handle, error, name);
		}

		inline void Property::apply(const Handle& handle, const std::string& name,
			const Format& format, bool data)
		{
			Property::validationParam(handle, name, format, data);
			int flag = data ? 1 : 0;
			Error error = ToError(mpv_set_property(handle.Data,
				name.data(), FromFormat(format), &flag));
			Property::validationSuccess(handle, error, name);
		}

		inline void Property::apply(const Handle& handle, const std::string& name,
			const Format& format, Node data)
		{
			Property::validationParam(handle, name, format, data);
			mpv_node node = data.translate();
			Error error = ToError(mpv_set_property(handle.Data,
				name.data(), FromFormat(format), &node));
			Property::validationSuccess(handle, error, name);
		}

		inline void Property::apply(const Handle& handle, const std::string& name,
			const Format& format, const std::string& data)
		{
			Property::validationParam(handle, name, format, data);
			Error error = ToError(mpv_set_property_string(
				handle.Data, name.c_str(),
				data.c_str()));
			Property::validationSuccess(handle, error, name);
		}

		//========================================================================
		// apply property asynchronously

		template<typename Ty>
		inline void Property::apply(const Handle& handle, const std::string& name,
			const Format& format, Ty data, const uint& replyData)
		{
			Property::validationParam(handle, name, format, data);
			Error error = ToError(mpv_set_property_async(
				handle.Data, replyData, name.data(),
				FromFormat(format), &data));
			Property::validationSuccess(handle, error, name);
		}

		inline void Property::apply(const Handle& handle, const std::string& name,
			const Format& format, bool data, const uint& replyData)
		{
			Property::validationParam(handle, name, format, data);
			int flag = data ? 1 : 0;
			Error error = ToError(mpv_set_property_async(
				handle.Data, replyData, name.data(),
				FromFormat(format), &flag));
			Property::validationSuccess(handle, error, name);
		}

		inline void Property::apply(const Handle& handle, const std::string& name,
			const Format& format, Node data, const uint& replyData)
		{
			Property::validationParam(handle, name, format, data);
			mpv_node node = data.translate();
			Error error = ToError(mpv_set_property_async(
				handle.Data, replyData, name.data(),
				FromFormat(format), &node));
			Property::validationSuccess(handle, error, name);
		}

		inline void Property::apply(const Handle& handle, const std::string& name,
			const Format& format, const std::string& data,
			const uint& replyData)
		{
			Property::validationParam(handle, name, format, data);
			const char* str = data.data();

			Error error = ToError(mpv_set_property_async(handle.Data,
				replyData, name.data(), FromFormat(format), &str));
			Property::validationSuccess(handle, error, name);
		}

		//========================================================================
		// acquire property synchronously or asynchronously

		template<typename Ty>
		inline void Property::acquire(const Handle& handle, const std::string& name,
			const Format& format, Ty& data)
		{
			Property::validationParam(handle, name, format, data);
			Error error = ToError(mpv_get_property(handle.Data,
				name.data(), FromFormat(format), &data));
			Property::validationSuccess(handle, error, name);
		}

		inline void Property::acquire(const Handle& handle, const std::string& name,
			const Format& format, bool& data)
		{
			Property::validationParam(handle, name, format, data);
			int flag = 0;
			Error error = ToError(mpv_get_property(handle.Data,
				name.data(), FromFormat(format), &flag));
			Property::validationSuccess(handle, error, name);
			data = (flag == 1) ? true : false;
		}

		inline void Property::acquire(const Handle& handle, const std::string& name,
			const Format& format, Node& data)
		{
			Property::validationParam(handle, name, format, data);
			mpv_node node{};

			Error error = ToError(mpv_get_property(handle.Data,
				name.data(), FromFormat(format), &node));

			data = node;
			mpv_free_node_contents(&node);
			Property::validationSuccess(handle, error, name);
		}

		inline void Property::acquire(const Handle& handle, const std::string& name,
			const Format& format, std::string& data)
		{
			Property::validationParam(handle, name, format, data);
			char* str = nullptr;

			Error error = ToError(mpv_get_property(handle.Data,
				name.data(), FromFormat(format), &str));

			Property::validationSuccess(handle, error, name);
			data.assign(str);
		}

		inline void Property::asyncAcquire(const Handle& handle, const std::string& name,
			const Format& format, const uint& replyData)
		{
			Property::validationParam(handle, name);
			Error error = ToError(mpv_get_property_async(handle.Data,
				replyData, name.data(), FromFormat(format)));
			Property::validationSuccess(handle, error, name);
		}

		//========================================================================
		// observe, unobserve and remove property

		inline void Property::observe(const Handle& handle, const std::string& name,
			const Format& format, const uint& replyData)
		{
			Property::validationParam(handle, name);
			Error error = ToError(mpv_observe_property(handle.Data,
				replyData, name.data(), FromFormat(format)));
			Property::validationSuccess(handle, error, name);
		}

		inline void Property::unobserve(const Handle& handle,
			const uint& replyData)
		{
			Property::validationParam(handle, "handle");
			int num = mpv_unobserve_property(
				handle.Data, replyData);
			if (num < 0) throw Exception(&handle,
				Error::Property, "unobserve");
		}

		inline void Property::remove(const Handle& handle,
			const std::string& name)
		{
			Property::validationParam(handle, name);
			Error error = ToError(mpv_del_property(
				handle.Data, name.data()));
			Property::validationSuccess(
				handle, error, name);
		}

		//========================================================================
		// validation of parameter(s) and the comfirmation of error

		inline void Property::validationParam(const Handle& handle,
			const std::string& name)
		{
			if (!handle || name.empty()) throw Exception(&handle,
				Error::InvalidParameter);
		}

		inline void Property::validationParam(const Handle& handle,
			const std::string& name, const Format& format,
			std::string data)
		{
			Property::validationParam(handle, name);
			if (format != Format::String && format != Format::OSDString)
				throw Exception(&handle, Error::Property, name);
		}

		inline void Property::validationParam(const Handle& handle,
			const std::string& name, const Format& format,
			ByteArray& data)
		{
			Property::validationParam(handle, name);
			if (format != Format::ByteArray) throw Exception(&handle,
				Error::Property, name);
		}

		inline void Property::validationParam(const Handle& handle,
			const std::string& name, const Format& format,
			long long data)
		{
			Property::validationParam(handle, name);
			if (format != Format::Int) throw Exception(&handle,
				Error::Property, name);
		}

		inline void Property::validationParam(const Handle& handle,
			const std::string& name, const Format& format,
			double& data)
		{
			Property::validationParam(handle, name);
			if (format != Format::Double) throw Exception(&handle,
				Error::Property, name);
		}

		inline void Property::validationParam(const Handle& handle,
			const std::string& name, const Format& format,
			Node& data)
		{
			Property::validationParam(handle, name);
			if (format != Format::Node) throw Exception(&handle,
				Error::Property, name);
		}

		inline void Property::validationParam(const Handle& handle,
			const std::string& name, const Format& format,
			bool& data)
		{
			Property::validationParam(handle, name);
			if (format != Format::BooleanInt) throw Exception(&handle,
				Error::Property, name);
		}

		inline void Property::validationSuccess(const Handle& handle,
			Error error, const std::string& name)
		{
			if (error != Error::Success) throw Exception(&handle,
				error, name);
		}

		//========================================================================
	}
}