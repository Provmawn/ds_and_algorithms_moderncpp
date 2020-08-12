#ifndef QUEUE_H
#define QUEUE_H
#include <cassert>
#include <initializer_list>
#include <iostream>
template<typename T>
class Queue 
{
public:
	Queue();
	Queue(const Queue &queue);
	Queue(Queue &&queue);
	Queue(std::initializer_list<T> list);
	~Queue();

	void enqueue(const T &data);
	const T& dequeue();
	bool empty() const;
	const T& front() const;

	T& operator=(const Queue &queue);
	T& operator=(Queue &&queue);

	friend std::ostream& operator<<(std::ostream &out, const Queue &queue) 
	{
		for (int i{ 0 }; i < queue.m_size; ++i) {
			out << queue.m_array[i] << ' ';
		}
		out << "size(" << queue.m_size << "), capacity(" << queue.m_capacity << "), back_index(" << queue.m_back_index << ')';
		return out;
	}
private:
	T *m_array{};
	int m_front_index{};
	int m_back_index{};
	int m_size{};
	int m_capacity{};

	bool full() const;
};

template<typename T>
Queue<T>::Queue()
	: m_array{ nullptr }
	, m_front_index{ 0 }
	, m_back_index{ 0 }
	, m_size{ 0 }
	, m_capacity{ 0 }
{
}

template<typename T>
Queue<T>::Queue(const Queue &queue) 
	: m_front_index{ queue.m_front_index }
	, m_back_index{ queue.m_back_index }
	, m_size{ queue.m_size }
	, m_capacity{ queue.m_capacity }
{
	// delete any previous data
	delete[] m_array;

	// perform a deep copy
	m_array = new T[m_capacity];
	for (int i{ 0 }; i < m_size; ++i) {
		m_array[i] = queue.m_array[i];
	}
}

template<typename T>
Queue<T>::Queue(Queue &&queue) 
	: m_array{ queue.m_array }
	, m_front_index{ queue.m_array }
	, m_back_index{ queue.m_back_index }
	, m_size{ queue.m_size}
	, m_capacity{ queue.m_capacity }
{
	queue.m_array = nullptr;
}

template<typename T>
Queue<T>::Queue(std::initializer_list<T> list)
	: m_front_index{ 0 }
	, m_back_index{ static_cast<int>(list.size()) - 1 }
	, m_size{ static_cast<int>(list.size()) }
	, m_capacity{ static_cast<int>(list.size()) }
{
	m_array = new T[m_capacity];
	int index{ 0 };
	for (const auto &element : list) 
	{
		m_array[index] = element;
		++index;
	}
}

template<typename T>
Queue<T>::~Queue() 
{
	delete[] m_array;
}

template<typename T>
void Queue<T>::enqueue(const T &data) 
{
	if (full()) 
	{
		// increase capacity by +1
		++m_capacity;
		T *temp_array{ new T[m_capacity] };
		for (int i{ 0 }; i < m_size; ++i)
			temp_array[i] = m_array[i];
		delete[] m_array;
		m_array = temp_array;
	}

	if (empty())
		m_array[m_back_index] = data;
	else 
		m_array[++m_back_index] = data;
	++m_size;
}

template<typename T>
const T& Queue<T>::dequeue() 
{
	assert(m_size >= 0);
	// return first element and shift list to remove first element
	auto front{ m_array[m_front_index] };

	for (int i{ 0 }; i < m_size - 1; ++i)
	{
		m_array[i] = m_array[i + 1];
	}
	--m_size;
	return front;
}

template<typename T>
bool Queue<T>::empty() const
{
	return m_size == 0;
}

template<typename T>
const T& Queue<T>::front() const
{
	return m_array[m_front_index];
}

template<typename T>
T& Queue<T>::operator=(const Queue &queue) 
{
	m_front_index = queue.m_front_index;
	m_back_index = queue.m_back_index;
	m_size = queue.m_size;
	m_capacity = queue.m_capacity;
	// delete any previous data
	delete[] m_array;

	// perform a deep copy
	m_array = new T[m_capacity];
	for (int i{ 0 }; i < m_size; ++i) {
		m_array[i] = queue.m_array[i];
	}
}

template<typename T>
T& Queue<T>::operator=(Queue &&queue) 
{
	m_array = queue.m_array;
	m_front_index = queue.m_array;
	m_back_index = queue.m_back_index;
	m_size = queue.m_size;
	m_capacity = queue.m_capacity;
	// prevent destructor from deleting the same array we copied
	queue.m_array = nullptr;
}

template<typename T>
bool Queue<T>::full() const 
{
	return (m_size == m_capacity);
}

#endif