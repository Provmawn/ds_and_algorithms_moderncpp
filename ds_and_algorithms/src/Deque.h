#ifndef DEQUE_H
#define DEQUE_H
#include <cassert>
#include <initializer_list>
#include <iostream>
template<typename T>
class Deque 
{
public:
	Deque();
	Deque(const Deque &deque);
	Deque(Deque &&deque);
	Deque(std::initializer_list<T> list);
	~Deque();

	void insert_front(const T &data);
	void insert_rear(const T &data);
	const T& remove_front();
	const T& remove_rear();

	T& operator=(const Deque &deque);
	T& operator=(Deque &&deque);

	friend std::ostream& operator<<(std::ostream &out, const Deque &deque)
	{
		for (int i{ 0 }; i < deque.m_size; ++i)
			out << deque.m_array[i] << ' ';
		out << " size(" << deque.m_size << ") capacity(" << deque.m_capacity << ')';
		return out;
	}
private:
	T *m_array{};
	int m_size{};
	int m_capacity{};

	bool full() const;
};

template<typename T>
Deque<T>::Deque()
	: m_size{ 0 }, m_capacity{ 0 }
{
}

template<typename T>
Deque<T>::Deque(const Deque &deque)
	: m_size{ deque.m_size }, m_capacity{ deque.m_capacity }
{
	delete[] m_array;
	m_array = new T[m_capacity];
	for (int i{ 0 }; i < m_size; ++i)
		m_array[i] = deque[i];
}

template<typename T>
Deque<T>::Deque(Deque &&deque) 
	: m_size{ deque.m_size }, m_capacity{ deque.m_capacity }
{
	m_array = deque.m_array;
	deque.m_array = nullptr;
}

template<typename T>
Deque<T>::Deque(std::initializer_list<T> list)
	: m_size{ static_cast<int>(list.size()) }, m_capacity{ static_cast<int>(list.size()) }
{
	m_array = new T[m_capacity];
	int index{ 0 };
	for (const auto &element : list) {
		m_array[index] = element;
		++index;
	}

}

template<typename T>
Deque<T>::~Deque()
{
	delete[] m_array;
}

template<typename T>
void Deque<T>::insert_front(const T &data)
{
	if (full()) 
	{
		++m_capacity;
		T *temp_array{ new T[m_capacity] };
		for (int i{ 0 }; i < m_size; ++i)
			temp_array[i] = m_array[i];
		delete[] m_array;
		m_array = temp_array;
	}
	// shift all elements right once
	for (int i{ m_size }; i > 0; --i)
		m_array[i] = m_array[i - 1];
	
	constexpr int front{ 0 };
	m_array[front] = data;
	++m_size;
}

template<typename T>
void Deque<T>::insert_rear(const T &data)
{
	if (full()) {
		++m_capacity;
		T *temp_array{ new T[m_capacity] };
		for (int i{ 0 }; i < m_size; ++i)
			temp_array[i] = m_array[i];
		delete[] m_array;
		m_array = temp_array;
	}
	m_array[m_size] = data;
	++m_size;
}

template<typename T>
const T& Deque<T>::remove_front()
{
	assert(m_array >= 0);
	constexpr int front{ 0 };
	auto ret{ m_array[front] };

	for (int i{ 0 }; i < m_size - 1; ++i) 
		m_array[i] = m_array[i + 1];
	--m_size;
	return ret;
}

template<typename T>
const T& Deque<T>::remove_rear()
{
	assert(m_size >= 0);
	--m_size;
	return m_array[m_size];
}

template<typename T>
T& Deque<T>::operator=(const Deque &deque)
{
	m_size = deque.m_size;
	m_capacity = deque.m_capacity;
	delete[] m_array;
	m_array = new T[m_capacity];
	for (int i{ 0 }; i < m_size; ++i)
		m_array[i] = deque[i];
}

template<typename T>
T& Deque<T>::operator=(Deque &&deque)
{
	m_size = deque.m_size;
	m_capacity = deque.m_capacity;
	m_array = deque.m_array;
	deque.m_array = nullptr;
}

template<typename T>
bool Deque<T>::full() const
{
	return (m_size == m_capacity);
}
#endif