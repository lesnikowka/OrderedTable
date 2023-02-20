#pragma once
#include <vector>
#include <algorithm>
#include <functional>

template <class T1, class T2>
class OrderTable{
	std::vector<T1, T2> _data;

	std::function<bool(const std::pair<T1, T2>&, const std::pair<T1, T2>&)> compare = [](const std::pair<T1, T2>& pair1, const std::pair<T1, T2>& pair1) {
		return pair1.first < pair2.first;
	};
public:
	class Iterator {
		typename std::vector<std::pair<T1, T2>>::iterator _iterator;

		friend class OrderTable;
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
		Iterator& operator--() {
			return --_iterator;
		}
	};
	Iterator begin() {
		return Iterator(_data.begin());
	}
	Iterator end() {
		return Iterator(_data.end());
	}
	void Add(const std::pair<T1, T2>& row) {
		_data.insert(std::upper_bound(_data.begin(), _data.end(), row, compare), row);
	}
	void Erase(const T1& key) {

	}
	void Erase(Iterator it) {
		_data.erase(it._iterator);
	}
	Iterator Find(const T1& key) {
		auto it = std::lower_bound(_data.begin(), _data.end(), key, compare);
		if ((*it).first == key) {
			return Iterator(it);
		}
		else {
			return end();
		}
	}
	bool Contains(const T1& key) {
		return Find(key) != end();
	}
};