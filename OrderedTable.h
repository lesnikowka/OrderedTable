#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

template <class T1, class T2>
class OrderedTable{
	std::vector<std::pair<T1, T2>> _data;

	class Iterator;
	class Comparator {
	public:
		bool operator()(const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2) {
			return p1.first < p2.first;
		}
		
		
	};
public:
	class Iterator {
		typename std::vector<std::pair<T1, T2>>::iterator _iterator;

		friend class OrderedTable;
	public:
		Iterator() = delete;
		Iterator(const typename std::vector<std::pair<T1, T2>>::iterator& iterator) : _iterator(iterator) {}
		Iterator(const Iterator& iterator) : _iterator(iterator._iterator) {}

		std::pair<T1, T2>& operator*() {
			return *_iterator;
		}
		Iterator& operator++() {
			return ++_iterator;
		}
		Iterator operator++(int) {
			Iterator result = *this;
			++result;
			return result;
		}
		Iterator& operator--() {
			return --_iterator;
		}
		Iterator operator--(int) {
			Iterator result = *this;
			--result;
			return result;
		}
		bool operator==(const Iterator& iterator) {
			return _iterator == iterator._iterator;
		}
		bool operator!=(const Iterator& iterator) {
			return _iterator != iterator._iterator;
		}
	};
	Iterator begin() {
		return Iterator(_data.begin());
	}
	Iterator end() {
		return Iterator(_data.end());
	}
	void Add(const std::pair<T1, T2>& row) {
		if (!Contains(row.first)) {
			Comparator comp;
			_data.insert(std::upper_bound(_data.begin(), _data.end(), row, comp), row);
		}
	}
	void Erase(const T1& key) {
		if (Contains(key)) {
			Comparator comp;
			_data.erase(std::lower_bound(_data.begin(), _data.end(), key, comp));
		}
		else {
			throw std::exception("Out of the bounds");
		}
	}
	void Erase(Iterator it) {
		_data.erase(it._iterator);
	}
	Iterator Find(const T1& key) {
		Comparator comp;
		std::pair<T1, T2> pair(key, T2());
		auto it = std::lower_bound(_data.begin(), _data.end(), pair, comp);
		
		if (it == _data.end() || (*it).first != key) {
			return end();
		}
		else {
			return Iterator(it);
		}
	}
	bool Contains(const T1& key) {
		return Find(key) != end();
	}
};