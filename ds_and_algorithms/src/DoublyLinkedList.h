#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "DoublyNode.h"
#include <cassert>
#include <initializer_list>
#include <iostream>
template<typename T>
class DoublyLinkedList 
{
public:
	DoublyLinkedList();
	//DoublyLinkedList(const DoublyLinkedList &doubly_linked_list);
	//DoublyLinkedList(DoublyLinkedList &&doubly_linked_list);
	//DoublyLinkedList(std::initializer_list<T> list);
	~DoublyLinkedList();

	bool empty() const;
	void push_front(const T &data);
	const T& pop_front();
	void push_back(const T &data);
	const T& pop_back();
	void insert_after(const T &lookup_data, const T &data);

	friend std::ostream& operator<<(std::ostream &out, const DoublyLinkedList &doubly_linked_list)
	{
		DoublyNode<T> *iterator{ doubly_linked_list.m_head };
		while (iterator != nullptr)
		{
			out << iterator->m_data << ' ';
			iterator = iterator->m_next;
		}
		return out;
	}

private:
	DoublyNode<T> *m_head{};
};

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList()
	: m_head{ nullptr }
{
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	DoublyNode<T> *iterator{ m_head };
	while (!empty())
	{
		if (m_head->m_next != nullptr)
		{
			iterator = m_head->m_next;
			delete m_head;
			m_head = iterator;
		}
		else
		{
			delete m_head;
			m_head = nullptr;
		}
	}
}

template<typename T>
bool DoublyLinkedList<T>::empty() const
{
	return (m_head == nullptr);
}

template<typename T>
void DoublyLinkedList<T>::push_front(const T &data)
{
	if (empty())
		m_head = new DoublyNode<T>(data);
	else {
		DoublyNode<T> *new_node{ new DoublyNode<T>(data) };
		m_head->m_prev = new_node;
		new_node->m_next = m_head;
		m_head = new_node;
	}
}

template<typename T>
const T& DoublyLinkedList<T>::pop_front()
{
	assert(!empty());
	T ret{ m_head->m_data };
	if (m_head->m_next) {					// if the head is pointing to something then make that object the new head
		DoublyNode<T> *front{ m_head };
		m_head = m_head->m_next;
		m_head->m_prev = nullptr;
		delete front;
		front = nullptr;
	}
	else									// if the head is not pointing to anything then delete it
	{
		delete m_head;
		m_head = nullptr;
	}
	return ret;
}

template<typename T>
void DoublyLinkedList<T>::push_back(const T &data)
{
	DoublyNode<T> *back{ m_head };
	while (back->m_next != nullptr)
		back = back->m_next;
	DoublyNode<T> *new_node{ new DoublyNode<T>{data} };
	back->m_next = new_node;
	new_node->m_prev = back;
}

template<typename T>
const T& DoublyLinkedList<T>::pop_back()
{
	assert(!empty());
	if (m_head->m_next == nullptr)
	{
		T ret{ m_head->m_data };
		delete m_head;
		m_head = nullptr;
		return ret;
	}
	DoublyNode<T> *back{ m_head };
	while (back->m_next)
		back = back->m_next;

	DoublyNode<T> *second_last{ back->m_prev };
	T ret{ back->m_data };
	delete back;
	back = nullptr;
	second_last->m_next = nullptr;
	return ret;
}

template<typename T>
void DoublyLinkedList<T>::insert_after(const T &lookup_data, const T &data)
{
	DoublyNode<T> *position_before{ m_head };
	while (position_before->m_next != nullptr && position_before->m_data != lookup_data)
		position_before = position_before->m_next;
	assert(position_before != nullptr);
	DoublyNode<T> *new_node{ new DoublyNode<T>{data} };
	DoublyNode<T> *position_after{ position_before->m_next };
	position_before->m_next = new_node;
	position_after->m_prev = new_node;
}
#endif