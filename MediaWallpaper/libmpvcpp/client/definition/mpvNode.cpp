#include"client/container/mpvNode.hpp"

using namespace mpv::client;

Node& Node::receive(const mpv_node& right)
{
	auto& Union = right.u;
	this->FormatType = ToFormat(right.format);

	switch (this->FormatType)
	{
	case Format::String:
	case Format::OSDString:
		this->String = Union.string;
		break;
	case Format::Double:
		this->Double = Union.double_;
		break;
	case Format::Int:
		this->Int = Union.int64;
		break;
	case Format::BooleanInt:
		this->Bool = static_cast<bool>(Union.flag);
		break;
	case Format::NodeMap:
		this->importMap(*Union.list);
		break;
	case Format::NodeArray:
		this->importArray(*Union.list);
		break;
	case Format::ByteArray:
		this->Byte.assign(Union.ba->data,
			Union.ba->size);
		break;
	default:
		break;
	}

	return *this;
}

mpv_node Node::translate()
{
	this->clearNode();
	auto& Union = this->node.u;
	this->node.format = FromFormat(this->FormatType);
	switch (this->FormatType)
	{
	case Format::String:
	case Format::OSDString:
		Union.string = this->exportString();
		break;
	case Format::Double:
		Union.double_ = this->Double;
		break;
	case Format::Int:
		Union.int64 = this->Int;
		break;
	case Format::BooleanInt:
		Union.flag = (this->Bool ? 1 : 0);
		break;
	case Format::NodeMap:
		Union.list = this->exportMap();
		break;
	case Format::NodeArray:
		Union.list = this->exportArray();
		break;
	case Format::ByteArray:
		Union.ba = this->exportByteArray();
		break;
	default:
		break;
	}

	return this->node;
}

void Node::clearNode()
{
	auto format = ToFormat(this->node.format);
	auto& Union = this->node.u;
	switch (this->FormatType)
	{
	case Format::String:
	case Format::OSDString:
		this->clearString(Union.string);
		break;
	case Format::Double:
		break;
	case Format::Int:
		break;
	case Format::BooleanInt:
		break;
	case Format::NodeMap:
		this->clearMap(Union.list);
		break;
	case Format::NodeArray:
		this->clearArray(Union.list);
		break;
	case Format::ByteArray:
		this->clearByteArray(Union.ba);
		break;
	default:
		break;
	}
}

void Node::importMap(const mpv_node_list& list)
{
	for (auto it = 0; it < list.num; it++) {
		this->Map[list.keys[it]] = list.values[it];
	}
}

void Node::importArray(const mpv_node_list& list)
{
	for (auto it = 0; it < list.num; it++) {
		this->Array.push_back(list.values[it]);
	}
}

char* Node::exportString()
{
	if (String.empty()) return nullptr;
	auto data = new char[String.size()];

	std::memcpy(data, String.data(),
		String.size());
	return data;
}

char* Node::exportString(const std::string& right)
{
	if (right.empty()) return nullptr;
	auto data = new char[right.size()];

	std::memcpy(data, right.data(),
		right.size());
	return data;
}

mpv_node_list* Node::exportMap()
{
	auto data = new mpv_node_list;
	size_t size = Map.size();

	if (size == 0) return nullptr;
	data->num = static_cast<int>(size);

	data->keys = new char* [size];
	data->values = new mpv_node[size];

	for (std::pair<MapIter, size_t> it(Map.begin(), 0);
		it.first != Map.end() && it.second < size;
		it.first++, it.second++)
	{
		auto& elem = it.first;

		data->keys[it.second] = this->exportString(elem->first);
		data->values[it.second] = elem->second.translate();
	}

	return data;
}

mpv_node_list* Node::exportArray()
{
	auto data = new mpv_node_list;
	size_t size = Array.size();

	if (size == 0) return nullptr;
	data->num = static_cast<int>(size);

	data->values = new mpv_node[size];
	size_t tick = 0;

	for (auto it = 0; it < size; it++)
	{
		data->values[tick] = Array[it].translate();
	}

	return data;
}

mpv_byte_array* Node::exportByteArray()
{
	if (Byte.empty()) return nullptr;
	auto ret = new mpv_byte_array;
	ret->size = Byte.size();
	Byte.copy(ret->data);

	return ret;
}