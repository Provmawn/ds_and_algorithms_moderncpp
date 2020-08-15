#ifndef DOUBLYNODE_H
#define DOUBLYNODE_H
#include <iostream>
template<typename T>
class DoublyNode
{
public:
	DoublyNode(const T &data);
	//DoublyNode(const DoublyNode &doubly_node);

	T m_data{};
	DoublyNode *m_next{};
	DoublyNode *m_prev{};
};

template<typename T>
DoublyNode<T>::DoublyNode(const T &data)
	: m_data{ data }, m_next{ nullptr }, m_prev{ nullptr }
{
}

/*
template<typename T>
DoublyNode<T>::DoublyNode(const DoublyNode &doubly_node)
	: m_data{ doubly_node.m_data }
{
	m_next{ new DoublyNode<T>{ doubly_node.m_next->m_data } };
	m_prev{ new DoublyNode<T>{ doubly_node.m_prev->m_data } };
}
*/

#endif