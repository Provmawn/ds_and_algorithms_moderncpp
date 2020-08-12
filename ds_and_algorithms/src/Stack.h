// template class for stack. function definitions are included in .h file
#ifndef STACK_H
#define STACK_H
#include <cassert>
#include <iostream>
#include <initializer_list>
template<typename T>
class Stack 
{ 
public:
	Stack();
	explicit Stack(const Stack &stack);
	explicit Stack(Stack &&stack);
	explicit Stack(std::initializer_list<T> list);
	~Stack();

	// core functions
	void push(const T &data);
	const T& pop();
	bool empty() const;
	const T& top() const;

	T& operator=(const Stack &stack);
	T& operator=(Stack &&stack);

	// friend function definition must be defined within class for template functions
	friend std::ostream& operator<<(std::ostream &out, const Stack &stack) {
		for (int i{ 0 }; i < stack.m_size; ++i)
			out << stack.m_array[i] << ' ';
		out << "size(" << stack.m_size << "), capacity(" << stack.m_capacity << ')';
		return out;
	}

private:
	T *m_array{};
	int m_size{};							// number of elements
	int m_capacity{};						// total memory allocated

	bool full() const;
};

 template<typename T>
Stack<T>::Stack() 
	: m_array{ nullptr }, m_size{ 0 }, m_capacity{ 0 }
{
}

template<typename T>
Stack<T>::Stack(const Stack &stack)
	: m_size{ stack.m_size }, m_capacity{ stack.m_capacity }
{
	assert(m_size >= 0);
	assert(m_capacity >= 0);
	m_array = new T[m_capacity]; 
	for (int i{ 0 }; i < m_size; ++i)
		m_array[i] = stack.m_array[i];
}

template<typename T>
Stack<T>::Stack(Stack &&stack) 
	: m_array{ stack.m_array }, m_size { stack.m_size }, m_capacity{ stack.m_capacity }
{
	// this is so the destructor of 'stack' does not delete the same pointer we assigned to our current object
	stack.m_array = nullptr;
}

template<typename T>
Stack<T>::Stack(std::initializer_list<T> list) 
	: m_array{ nullptr }, m_size{ static_cast<int>(list.size()) }, m_capacity{ static_cast<int>(list.size()) }
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
Stack<T>::~Stack() {
	delete[] m_array;
}

template<typename T>
void Stack<T>::push(const T &data) 
{
	// check if we have enough space allocated in the array
	if (full()) 
	{
		// create a new array that is +1 capacity
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
const T& Stack<T>::pop() 
{
	assert(m_size >= 1);
	return m_array[--m_size];
}

template<typename T>
bool Stack<T>::empty() const 
{
	return (m_size == 0);
}

template<typename T>
const T& Stack<T>::top() const 
{
	assert(m_size >= 1);
	// return the last element in the array
	return m_array[m_size - 1];
}

template<typename T>
T& Stack<T>::operator=(const Stack &stack) 
{
	if (&stack == this)
		return *this;

	// delete any previous allocation
	delete[] m_array;

	m_size = stack.m_size;
	m_capacity = stack.m_capacity;
	m_array = new T[m_capacity]; 
	for (int i{ 0 }; i < m_size; ++i)
		m_array[i] = stack.m_array[i];

	return *this;
}

template<typename T>
T& Stack<T>::operator=(Stack &&stack) 
{
	// self assignment;
	if (&stack == this)
		return *this;

	// delete any previous allocation
	delete[] m_array;

	m_array = stack.m_array;
	m_size = stack.m_size;
	m_capacity = stack.m_capacity;

	// this is so the destructor of 'stack' does not delete the same pointer we assigned to our current object
	stack.m_array = nullptr;

	return *this;
}

template<typename T>
bool Stack<T>::full() const {
	return (m_size == m_capacity);
}
#endif