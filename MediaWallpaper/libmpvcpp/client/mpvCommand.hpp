#pragma once
#include"client/container/mpvNode.hpp"
#include"mpvHandle.hpp"

#include<vector>

namespace mpv
{
	namespace client
	{
		class Command
		{
			using StringArgs = std::vector<std::string>;
			using ArgsIter = StringArgs::const_iterator;
			using CharPtr = std::unique_ptr<const char*>;
		public:
			static inline void sync(const Handle& handle,
				const StringArgs& args);

			static inline void sync(const Handle& handle,
				Node& args, Node& result);

			static inline void async(const Handle& handle, const StringArgs& args,
				const size_t& replyData);

			static inline void async(const Handle& handle, Node& args,
				const size_t& replyData);
		public:
			static inline void acquire(const Handle& handle,
				const StringArgs& args,
				Node& result);

			static inline void string(const Handle& hadle,
				const std::string& args);
		protected:
			static inline void validationParam(const Handle& handle,
				const StringArgs& args);

			static inline void validationSuccess(const Handle& handle,
				Error error, const std::string& name = "no name");

			static CharPtr Convert(const StringArgs& args);
		};

		inline void Command::sync(const Handle& handle,
			const Command::StringArgs& args)
		{
			Command::validationParam(handle, args);
			CharPtr data = Convert(args);

			Error error = ToError(mpv_command(
				handle.Data, data.get()));

			Command::validationSuccess(handle, error, "command with " + args.at(0));
		}

		inline void Command::sync(const Handle& handle, Node& args, Node& result)
		{
			mpv_node node = args.translate();
			mpv_node ret{};

			Error error = ToError(mpv_command_node(
				handle.Data, &node, &ret));

			Command::validationSuccess(handle, error, "command with node");
		}

		inline void Command::async(const Handle& handle, const StringArgs& args,
			const size_t& replyData)
		{
			Command::validationParam(handle, args);
			CharPtr data = Convert(args);

			Error error = ToError(mpv_command_async(handle.Data,
				replyData, data.get()));

			Command::validationSuccess(handle, error, args.at(0));
		}

		inline void Command::async(const Handle& handle, Node& args,
			const size_t& replyData)
		{
			mpv_node node = args.translate();

			Error error = ToError(mpv_command_node_async(
				handle.Data, replyData, &node));

			Command::validationSuccess(handle, error, "command with node");
		}

		inline void Command::acquire(const Handle& handle,
			const StringArgs& args,
			Node& result)
		{
			Command::validationParam(handle, args);
			CharPtr data = Convert(args);
			mpv_node node{};

			Error error = ToError(mpv_command_ret(handle.Data,
				data.get(), &node));

			result = node;
			mpv_free_node_contents(&node);
			Command::validationSuccess(handle, error, "command with " + args.at(0));
		}

		inline void Command::string(const Handle& handle,
			const std::string& args)
		{
			if (!handle || args.empty())
			{
				throw Exception(&handle, Error::InvalidParameter,
					"command with string");
			}

			Error error = ToError(mpv_command_string(
				handle.Data, args.data())
			);

			Command::validationSuccess(handle, error, "command with " + args);
		}

		inline void Command::validationParam(const Handle& handle,
			const StringArgs& args)
		{
			if (!handle || args.empty())
			{
				throw Exception(&handle, Error::InvalidParameter,
					"command with string vector");
			}
		}

		inline void Command::validationSuccess(const Handle& handle,
			Error error, const std::string& name)
		{
			if (!handle || (error != Error::Success))
			{
				throw Exception(&handle, error, name);
			}
		}
	}
}