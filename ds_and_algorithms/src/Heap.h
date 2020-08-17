#ifndef HEAP_H
#define HEAP_H
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <vector>
template<typename T>
class Heap 
{
public:
	Heap() = delete;
	Heap(std::initializer_list<T> list);

	void insert(const T &data);
	const T& pop();

	friend std::ostream& operator<<(std::ostream &out, const Heap &heap)
	{
		for (const auto &element : heap.vector)
			out << element << ' ';
		return out;
	}

private:
	int parentIndex(int child_index);
	int leftChildIndex(int parent_index);
	int rightChildIndex(int parent_index);
	std::vector<T> vector{};
	int m_size{};

	void bottomUpHeapify(int child_index);
	void topDownHeapify(int parent_index);
};

template<typename T>
Heap<T>::Heap(std::initializer_list<T> list)
	: vector{ list }, m_size{ static_cast<int>(list.size()) }
{
	int last_index{ m_size - 1 };
	int leaves{  last_index / 2 };
	for (int i{ leaves }; i < m_size; ++i)
		bottomUpHeapify(i);
}

template<typename T>
void Heap<T>::insert(const T &data)
{
	int current{ m_size };
	vector.push_back(data);
	++m_size;

	bottomUpHeapify(current);
}

template<typename T>
const T& Heap<T>::pop()
{
	constexpr int first{ 0 };
	int last{ m_size - 1 };
	T ret{ vector[first] };
	std::swap(vector[first], vector[last]);
	vector.pop_back();
	--m_size;

	topDownHeapify(first);

	return ret;
}

template<typename T>
int Heap<T>::parentIndex(int child_index)
{
	return (child_index - 1) / 2  ;
}

template<typename T>
int Heap<T>::leftChildIndex(int parent_index)
{
	return (2 * parent_index + 1);
}

template<typename T>
int Heap<T>::rightChildIndex(int parent_index)
{
	return (2 * parent_index + 2);
}

template<typename T>
void Heap<T>::bottomUpHeapify(int child_index)
{
	if (child_index == 0) 
		return;
	int parent{ parentIndex(child_index) };
	// if child is greater then parent do a swap
	if (vector[child_index] > vector[parent])
		std::swap(vector[child_index], vector[parent]);
	bottomUpHeapify(parent);
}

template<typename T>
void Heap<T>::topDownHeapify(int parent_index)
{
	// base case of parent being equal to the last index
	int last{ m_size - 1 };
	if (parent_index == last)
		return;

	// keep track of the largest index, left child index, and right child index
	int largest{ parent_index };
	int left{ leftChildIndex(parent_index) };
	int right{ rightChildIndex(parent_index) };
	// make sure left and right are valid indicies
	if (left >= m_size && right >= m_size)
		return;
	if (left >= m_size)
		largest = right;
	else if (right >= m_size)
		largest = left;
	else {
		// if parent is less than child do a swap with the smaller child
		if (vector[parent_index] < vector[left]
			&& vector[right] <= vector[left])
		{
			largest = left;
		}
		// might be able to make this an 'else' statement
		if (vector[parent_index] < vector[right]
			&& vector[left] <= vector[right])
		{
			largest = right;
		}
	}
	// this means the node is positioned correctly
	if (largest == parent_index)
		return;
	std::swap(vector[parent_index], vector[largest]);
	topDownHeapify(largest);
}
#endif
