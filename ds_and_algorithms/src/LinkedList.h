#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include <cassert>
#include <initializer_list>
#include <iostream>
#include <iterator>
template<typename T>
class LinkedList 
{
public:
	LinkedList();
	LinkedList(LinkedList &&linked_list);
	LinkedList(std::initializer_list<T> list);
	~LinkedList();

	bool empty() const;
	void push_front(const T &data);
	const T& pop_front();
	void push_back(const T &data);
	const T& pop_back();
	void insert_after(const T &lookup_data, const T &data);


	friend std::ostream& operator<<(std::ostream &out, const LinkedList &list)
	{
		Node<T> *current{ list.m_head };
		while (current)
		{
			std::cout << current->m_data << ' ';
			current = current->m_next;
		}
		return out;
	}
private:
	Node<T> *m_head{};
};

template<typename T>
LinkedList<T>::LinkedList()
	: m_head{ nullptr }
{
}

template<typename T>
LinkedList<T>::LinkedList(LinkedList &&linked_list)
	: m_head{ linked_list.m_head }
{
	linked_list.m_head = nullptr;
}

template<typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> list)
	: m_head{ nullptr }
{
	for (auto iterator{ std::rbegin(list) }; iterator != std::rend(list); ++iterator)
	{
		Node<T> *new_node{ new Node<T>{ *iterator } };
		if (m_head)
			new_node->m_next = m_head;
		m_head = new_node;
	}
}

template<typename T>
LinkedList<T>::~LinkedList()
{
	std::cout << "LinkedList destroyed\n";
	while (!empty()) 
	{
		Node<T> *current{ m_head };
		m_head = m_head->m_next;
		delete current;
	}
}

template<typename T>
bool LinkedList<T>::empty() const
{
	return (m_head == nullptr);
}

template<typename T>
void LinkedList<T>::push_front(const T &data)
{
	Node<T> *new_node{ new Node<T>{ data } };
	new_node->m_next = m_head;
	m_head = new_node;
}

template<typename T>
const T& LinkedList<T>::pop_front()
{
	const T& data{ m_head->m_data };
	Node<T> *current{ m_head };
	m_head = m_head->m_next;
	delete current;
	return data;
}

template<typename T>
void LinkedList<T>::push_back(const T &data)
{
	Node<T> *last{ m_head };
	while (last->m_next != nullptr)
		last = last->m_next;

	last->m_next = new Node<T>{ data };
}

template<typename T>
const T& LinkedList<T>::pop_back() 
{
	Node<T> *second_last{ m_head };
	assert(second_last != nullptr);
	if (second_last->m_next == nullptr)
	{
		const T &ret{ m_head->m_data };
		delete m_head;
		m_head = nullptr;
		return ret;
	}
	while (second_last->m_next->m_next != nullptr)
		second_last = second_last->m_next;

	const T &ret{ second_last->m_next->m_data };
	delete second_last->m_next;
	second_last->m_next = nullptr;
	return ret;
}

template<typename T>
void LinkedList<T>::insert_after(const T &lookup_data, const T &data)
{
	Node<T> *after{ m_head };
	while (after->m_next != nullptr && after->m_data != lookup_data)
		after = after->m_next;
	if (after->m_next == nullptr)
		return;
	Node<T> *new_node{ new Node<T>{ data } };
	new_node->m_next = after->m_next;
	after->m_next = new_node;
}

#endif