#include"client/mpvCommand.hpp"

using namespace mpv::client;

Command::CharPtr Command::Convert(const Command::StringArgs& args)
{
	size_t size = args.size();
	CharPtr data(new const char* [size]);
	for (std::pair<size_t, ArgsIter> it(0, args.begin());
		it.first <= size && (it.second != args.end());
		it.first++, it.second++)
	{
		if (it.second->empty())
		{
			data.operator->()[it.first] = nullptr;
			continue;
		}
		else if (*it.second == "nullptr" || *it.second == "null")
		{
			data.operator->()[it.first] = nullptr;
			continue;
		}

		data.operator->()[it.first] = it.second->c_str();
	}

	return data;
}