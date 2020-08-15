#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <cassert>
#include <cstddef> // std::size_t
#include <functional> // std::hash
#include <iostream>
#include <list>
#include <utility>
template<typename T1, typename T2>
class Hashtable {
public:
	Hashtable() = default;
	Hashtable(int capacity);

	void insert(std::pair<T1, T2> key_value_pair);
	const T2& find(const T1 &key);
	std::size_t hash(T1 key);

	friend std::ostream& operator<<(std::ostream &out, const Hashtable &hashtable)
	{
		for (int i{ 0 }; i < hashtable.m_capacity; ++i)
			for (const auto &element : hashtable.m_table[i])
				std::cout << element << ' ';
		return out;
	}
private:
	std::list<T2> *m_table{};
	int m_size{};
	int m_capacity{};
};

template<typename T1, typename T2>
Hashtable<T1, T2>::Hashtable(int capacity)
	: m_capacity{ capacity }
{
	assert(m_capacity >= 0);
	m_table = new std::list<T2>[capacity];
}

template<typename T1, typename T2>
void Hashtable<T1, T2>::insert(std::pair<T1, T2> key_value_pair)
{
	std::size_t index{ hash(key_value_pair.first) };
	m_table[index].push_back(key_value_pair.second);
}

template<typename T1, typename T2>
const T2& Hashtable<T1, T2>::find(const T1 &key)
{
	std::size_t index{ hash(key) };
	return m_table[index];
}

template<typename T1, typename T2>
std::size_t Hashtable<T1, T2>::hash(T1 key)
{
	return std::hash<T1>{}(key) % m_capacity;
}
#endif
