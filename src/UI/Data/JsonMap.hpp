#pragma once
#include<initializer_list>
#include<unordered_map>
#include<vector>

namespace UI
{
	template<typename Left, typename Right>
	class JsonMap
	{
	public:
		class forward_iterator;
		class reverse_iterator;

		inline JsonMap() {}
		inline ~JsonMap() {}

		inline JsonMap(const JsonMap& right) { this->assign(right); }
		inline JsonMap(std::initializer_list<std::pair<Left, Right> > initList) :Elem(initList) {}
	public:
		inline void push(const Left& key, const Right& value = Right())
		{
			auto it = IndexMap.find(key);
			if (it == IndexMap.end()) {
				Elem.push_back(std::pair<Left, Right>(key, value));
				IndexMap[key] = this->size() - 1;
				return;
			}

			static_cast<std::pair<Left, Right>&>(
				Elem.at(it->second)
				).second = value;
		}

		inline JsonMap& assign(const JsonMap& right)
		{
			if (this == &right) return *this;

			Elem.assign(right.Elem.begin(), right.Elem.end());
			IndexMap = right.IndexMap;

			return *this;
		}

		inline JsonMap& swap(JsonMap& right)
		{
			if (this == &right) return *this;

			std::swap(IndexMap, right.IndexMap);
			std::swap(Elem, right.Elem);

			return *this;
		}

		inline size_t size() const { return Elem.size(); }
		inline bool empty() const { return Elem.empty(); }

		inline reverse_iterator rend() const { return reverse_iterator(*this, Elem.size()); }
		inline reverse_iterator rbegin() const { return reverse_iterator(*this, 0); }
		inline reverse_iterator rfind(const Left& key) const
		{
			for (auto it = this->rbegin(); it != this->end(); ++it)
				if (it.key() == key)
					return it;

			return this->rend();
		}

		inline forward_iterator end() const { return forward_iterator(*this, Elem.size()); }
		inline forward_iterator begin() const { return forward_iterator(*this, 0); }
		inline forward_iterator find(const Left& key) const
		{
			for (auto it = this->begin(); it != this->end(); ++it)
				if (it.key() == key)
					return it;

			return this->end();
		}
	public:
		inline JsonMap& operator=(const JsonMap& right) { return this->assign(right); }

		inline const Right& operator[](const Left& key) const
		{
			forward_iterator it = this->find(key);
			if (it == this->end()) {
				return static_cast<const std::pair<Left, Right>&>(
					Elem.at(-1)).second;
			}

			return it.value();
		}

		inline Right& operator[](const Left& key)
		{
			forward_iterator it = this->find(key);
			if (it == this->end())
			{
				this->push(key);
				auto test = this->end();
				return this->end().value();
			}

			return it.value();
		}
	private:
		std::unordered_map<Left, size_t> IndexMap;
		std::vector<std::pair<Left, Right> > Elem;
	};

	template<typename Left, typename Right>
	class JsonMap<Left, Right>::forward_iterator
	{
	public:
		inline forward_iterator(const JsonMap& map, size_t position)
		{
			Elem = const_cast<std::vector<std::pair<Left, Right> >*>(&map.Elem);
			Shift = map.Elem.size();

			this->shiftPosition(position);
		}

		inline forward_iterator(const forward_iterator& right, size_t position)
		{
			Elem = right.Elem;
			Shift = right.Shift;
			this->shiftPosition(position);
		}

		inline forward_iterator() {}
		inline ~forward_iterator() {}
	public:
		friend inline forward_iterator operator+(size_t offset, const forward_iterator& iter) { return forward_iterator(iter, Position + offset); }
		friend inline forward_iterator operator-(size_t offset, const forward_iterator& iter) { return forward_iterator(iter, Position - offset); }
		inline forward_iterator operator+(size_t offset) { return forward_iterator(*this, Position + offset); }
		inline forward_iterator operator-(size_t offset) { return forward_iterator(*this, Position - offset); }
		inline bool operator==(const forward_iterator& right) { return Position == right.Position; }
		inline bool operator!=(const forward_iterator& right) { return !this->operator==(right); }
		inline void operator++(int) { this->shiftPosition(Position + 1); }
		inline void operator--(int) { this->shiftPosition(Position - 1); }
		inline const forward_iterator& operator*() const { return *this; }
		inline forward_iterator& operator*() { return *this; }

		inline forward_iterator& operator++() noexcept
		{
			this->shiftPosition(Position + 1);
			return *this;
		}
		inline forward_iterator& operator--() noexcept
		{
			this->shiftPosition(Position - 1);
			return *this;
		}
	public:
		inline const Right& value() const { return static_cast<const std::pair<Left, Right>& >(Elem->at(this->pos())).second; }
		inline const Left& key() const { return static_cast<const std::pair<Left, Right>& >(Elem->at(this->pos())).first; }
		inline Right& value() { return static_cast<std::pair<Left, Right>& >(Elem->at(this->pos())).second; }
		inline Left& key() { return static_cast<std::pair<Left, Right>& >(Elem->at(this->pos())).first; }
		inline size_t pos() const { return Position == Shift ? Position - 1 : Position; }
	private:
		inline void shiftPosition(const size_t& position) noexcept
		{
			Position = position > Shift ? Shift : position;
		}
	private:
		std::vector<std::pair<Left, Right> >* Elem = nullptr;
		size_t Position = 0;
		size_t Shift = 0;
	};

	template<typename Left, typename Right>
	class JsonMap<Left, Right>::reverse_iterator
	{
	public:
		inline reverse_iterator(const JsonMap& map, size_t position)
		{
			Elem = const_cast<std::vector<std::pair<Left, Right> >*>(&map.Elem);
			Shift = map.Elem.size();

			this->shiftPosition(position);
		}

		inline reverse_iterator(const reverse_iterator& right, size_t position)
		{
			Elem = right.Elem;
			Shift = right.Shift;
			this->shiftPosition(position);
		}

		inline reverse_iterator() {}
		inline ~reverse_iterator() {}
	public:
		friend inline reverse_iterator operator+(size_t offset, const reverse_iterator& iter) { return reverse_iterator(iter, Position + offset); }
		friend inline reverse_iterator operator-(size_t offset, const reverse_iterator& iter) { return reverse_iterator(iter, Position - offset); }
		inline reverse_iterator operator+(size_t offset) { return reverse_iterator(*this, Position + offset); }
		inline reverse_iterator operator-(size_t offset) { return reverse_iterator(*this, Position - offset); }
		inline bool operator==(const reverse_iterator& right) { return Position == right.Position; }
		inline bool operator!=(const reverse_iterator& right) { return !this->operator==(right); }
		inline void operator++(int) { this->shiftPosition(Position + 1); }
		inline void operator--(int) { this->shiftPosition(Position - 1); }
		inline const reverse_iterator& operator*() const { return *this; }
		inline reverse_iterator& operator*() { return *this; }

		inline reverse_iterator& operator++() noexcept
		{
			this->shiftPosition(Position + 1);
			return *this;
		}
		inline reverse_iterator& operator--() noexcept
		{
			this->shiftPosition(Position - 1);
			return *this;
		}
	public:
		inline const Right& value() const { return static_cast<const std::pair<Left, Right>&>(Elem->at(this->pos())).second; }
		inline const Left& key() const { return static_cast<const std::pair<Left, Right>&>(Elem->at(this->pos())).first; }
		inline Right& value() { return static_cast<std::pair<Left, Right>&>(Elem->at(this->pos())).second; }
		inline Left& key() { return static_cast<std::pair<Left, Right>&>(Elem->at(this->pos())).first; }
		inline size_t pos() const { return Position == Shift ? 0 : Shift - Position - 1; }
	private:
		inline void shiftPosition(size_t position)
		{
			Position = position > Shift ? Shift : position;
		}
	private:
		std::vector<std::pair<Left, Right> >* Elem = nullptr;
		size_t Position = 0;
		size_t Shift = 0;
	};
}
