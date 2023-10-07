#pragma once
#include"client/code/mpvFormat.hpp"
#include"mpvByteArray.hpp"

#include<unordered_map>
#include<vector>
#include<string>

namespace mpv
{
	namespace client
	{
		class Node
		{
		public:
			Format FormatType = Format::None;
			std::string String = "";
			double Double = 0.0;
			long long Int = 0;
			bool Bool = false;

			std::unordered_map<std::string, Node> Map;
			std::vector<Node> Array;
			ByteArray Byte;
		public:
			inline Node() {}
			inline Node(const mpv_node& right) { this->receive(right); }
			inline Node& operator=(const mpv_node& right) { return this->receive(right); }

			inline Node(const Node& right) { this->receive(right); }
			inline Node& operator=(const Node& right) { return this->receive(right); }

			Node& receive(const mpv_node& right);
			inline Node& receive(const Node& right);

			mpv_node translate();

			inline ~Node() { this->clearNode(); }
		private:
			void clearNode();

			void importMap(const mpv_node_list& list);
			void importArray(const mpv_node_list& list);

			char* exportString();
			char* exportString(const std::string& right);

			mpv_node_list* exportMap();
			mpv_node_list* exportArray();
			mpv_byte_array* exportByteArray();

			inline void clearString(char*& str);
			inline void clearMap(mpv_node_list*& list);
			inline void clearArray(mpv_node_list*& list);
			inline void clearByteArray(mpv_byte_array*& byteArray);
		private:
			using MapIter = std::unordered_map<std::string, Node>::iterator;

			mpv_node node{};
		};

		inline Node& Node::receive(const Node& right)
		{
			if (&right == this) return *this;

			this->FormatType = right.FormatType;
			this->String = right.String;
			this->Double = right.Double;

			this->Int = right.Int;
			this->Bool = right.Bool;

			this->Map = right.Map;
			this->Byte = right.Byte;

			this->Array.assign(right.Array.begin(),
				right.Array.end());

			return *this;
		}

		inline void Node::clearString(char*& str)
		{
			delete[] str;
			str = nullptr;
		}

		inline void Node::clearMap(mpv_node_list*& list)
		{
			if (list == nullptr) return;
			auto size = list->num;

			for (auto it = 0; it < size; it++)
				delete[] list->keys[it];
			delete[] list->values;
			delete[] list->keys;
			delete list;

			list = nullptr;
		}

		inline void Node::clearArray(mpv_node_list*& list)
		{
			if (list == nullptr) return;
			delete[] list->values;

			delete list;
			list = nullptr;
		}

		inline void Node::clearByteArray(mpv_byte_array*& byteArray)
		{
			if (byteArray == nullptr) return;
			delete[] byteArray->data;

			delete byteArray;
			byteArray = nullptr;
		}
	}
}