#pragma once
#include<vector>

namespace UI
{
	template<typename LType, typename RType>
	class JsonMap
	{
	public:
		inline JsonMap() {}
		inline ~JsonMap() {}
		class forward_iterator;
		class reverse_iterator;
	public:
		inline JsonMap(const JsonMap& right) { this->assign(right); }

		inline JsonMap& swap(JsonMap& right);
		inline JsonMap& assign(const JsonMap& right);

		inline bool empty() const { return Key.empty(); }
		inline size_t size() const { return Key.size(); }
		inline void push(const LType& key, const RType& value);

		inline forward_iterator begin() const { return forward_iterator(*this, 0); }
		inline forward_iterator end() const { return forward_iterator(*this, Key.size() - 1); }

		inline reverse_iterator rend() const { return reverse_iterator(*this, 0); }
		inline reverse_iterator rbegin() const { return reverse_iterator(*this, Key.size() - 1); }

		inline forward_iterator find(const LType& key) const
		{
			for (auto it = this->begin(); it != this->end(); it++)
			{
				if (key == it.key())
					return it;
			}

			return this->end();
		}

		inline reverse_iterator rfind(const LType& key) const
		{
			for (auto it = this->rbegin(); it != this->rend(); it++)
			{
				if (key == it.key())
					return it;
			}

			return this->rend();
		}

		inline RType& operator[](const LType& key);
		inline const RType& operator[](const LType& key) const;
	private:
		std::vector<LType> Key;
		std::vector<RType> Value;
	};

	template<typename LType, typename RType>
	class JsonMap<LType, RType>::forward_iterator
	{
	public:
		inline forward_iterator(const JsonMap& reference, size_t position = 0)
			:Position(position)
		{
			Value = const_cast<std::vector<RType>*>(&reference.Value);
			Key = const_cast<std::vector<LType>*>(&reference.Key);
		}

		inline forward_iterator() {};

		inline const RType& value() const { return Value->at(Position); }
		inline const LType& key() const { return Key->at(Position); }
		inline RType& value() { return Value->at(Position); }
		inline LType& key() { return Key->at(Position); }

		friend inline forward_iterator operator+(size_t shift, forward_iterator iter)
		{
			iter.Position += shift;
			return iter;
		}

		inline const forward_iterator operator*() const { return *this; }

		inline forward_iterator operator+(size_t shift)
		{
			Position += shift;
			return *this;
		}

		inline forward_iterator operator-(size_t shift)
		{
			Position -= shift;
			return *this;
		}

		inline bool operator!=(const forward_iterator& right) const
		{
			return (Position != right.Position + 1);
		}

		inline bool operator==(const forward_iterator& right) const
		{
			return !this->operator!=(right);
		}

		inline forward_iterator& operator++() noexcept
		{
			++Position;
			return *this;
		}

		inline void operator++(int)
		{
			Position++;
		}
	private:
		size_t Position = 0;
		std::vector<LType>* Key = nullptr;
		std::vector<RType>* Value = nullptr;
	};

	template<typename LType, typename RType>
	class JsonMap<LType, RType>::reverse_iterator
	{
	public:
		inline reverse_iterator(const JsonMap& reference, size_t position = 0)
			:Position(position)
		{
			Value = const_cast<std::vector<RType>*>(&reference.Value);
			Key = const_cast<std::vector<LType>*>(&reference.Key);
		}

		inline reverse_iterator() {};

		inline const RType& value() const { return Value->at(Position); }
		inline const LType& key() const { return Key->at(Position); }
		inline RType& value() { return Value->at(Position); }
		inline LType& key() { return Key->at(Position); }

		friend inline reverse_iterator operator+(size_t shift, reverse_iterator iter)
		{
			iter.Position += shift;
			return iter;
		}

		inline reverse_iterator operator+(size_t shift)
		{
			Position -= shift;
			return *this;
		}

		inline reverse_iterator operator-(size_t shift)
		{
			Position += shift;
			return *this;
		}

		inline bool operator!=(const reverse_iterator& right) const
		{
			return (Position + 1 != right.Position);
		}

		inline bool operator==(const reverse_iterator& right) const
		{
			return !this->operator!=(right);
		}

		inline reverse_iterator& operator++()
		{
			--Position;
			return *this;
		}

		inline void operator++(int) noexcept
		{
			Position--;
		}
	private:
		size_t Position = 0;
		std::vector<LType>* Key = nullptr;
		std::vector<RType>* Value = nullptr;
	};

	template<typename LType, typename RType>
	inline JsonMap<LType, RType>& JsonMap<LType, RType>::swap(JsonMap<LType, RType>& right)
	{
		if (this == &right) return *this;
		Value.swap(right.Value);
		Key.swap(right.Key);
		return *this;
	}

	template<typename LType, typename RType>
	inline JsonMap<LType, RType>& JsonMap<LType, RType>::assign(const JsonMap<LType, RType>& right)
	{
		if (this == &right) return *this;
		Value.assign(right.Value.begin(),
			right.Value.end());
		Key.assign(right.Key.begin(),
			right.Key.end());
		return *this;
	}

	template<typename LType, typename RType>
	inline void JsonMap<LType, RType>::push(const LType& key, const RType& value)
	{
		Value.push_back(value);
		Key.push_back(key);
	}

	template<typename LType, typename RType>
	inline RType& JsonMap<LType, RType>::operator[](const LType& key)
	{
		size_t index = 0;
		for (auto it = Key.begin(); it != Key.end(); it++)
		{
			index = std::distance(Key.begin(), it);
			if (*it == key)
			{
				return Value.at(index);
			}
		}

		this->push(key, RType());
		return Value.back();
	}

	template<typename LType, typename RType>
	inline const RType& JsonMap<LType, RType>::operator[](const LType& key) const
	{
		size_t index = 0;
		for (auto it = Key.begin(); it != Key.end(); it++)
		{
			index = std::distance(Key.begin(), it);
			if (*it == key)
			{
				return Value.at(index);
			}
		}

		return Value.at(static_cast<unsigned long long>(-1));
	}
}
