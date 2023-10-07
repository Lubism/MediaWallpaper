#pragma once
#include"client/mpvException.hpp"

#include<memory>

namespace mpv
{
	namespace client
	{
		class ByteArray
		{
		public:
			inline ByteArray() {}
			inline ByteArray(const ByteArray& right) { this->assign(right); }
			inline ByteArray(void*& data, size_t length) { this->assign(data, length); }
			inline ByteArray& operator=(const ByteArray& right) { return this->assign(right); }
		public:
			inline void allocate(size_t& length);

			inline void assign(void*& data, size_t& length);

			inline ByteArray& assign(const ByteArray& right);

			inline void copy(void*& dst) const;

			inline bool empty() const;

			inline size_t size() const;
		public:
			inline ~ByteArray() { }
		private:
			std::unique_ptr<unsigned char> Data;
			size_t Length = 0;
		};

		inline void ByteArray::allocate(size_t& length)
		{
			if (length == 0)
			{
				throw Exception(this, "Allocation length is invalid !");
			}

			Data.reset(new unsigned char[length]);
			this->Length = length;
		}

		inline void ByteArray::assign(void*& data, size_t& length)
		{
			if (length == 0)
			{
				throw Exception(this, "Allocation length is invalid !");
			}

			this->allocate(length);
			std::memcpy(this->Data.get(), data, length);
		}

		inline ByteArray& ByteArray::assign(const ByteArray& right)
		{
			this->Length = right.Length;
			if (this->Length == 0) return *this;
			this->Data.reset(new unsigned char[right.Length]);
			std::memcpy(this->Data.get(), right.Data.get(), right.Length);

			return *this;
		}

		inline void ByteArray::copy(void*& dst) const
		{
			dst = new unsigned char[this->Length];
			std::memcpy(dst, this->Data.get(), this->Length);
		}

		inline bool ByteArray::empty() const
		{
			return (this->Length == 0);
		}

		inline size_t ByteArray::size() const
		{
			return this->Length;
		}
	}
}