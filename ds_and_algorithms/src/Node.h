#ifndef NODE_H
#define NODE_H
#include <iostream> // remove with destructor
#include <memory>
template<typename T>
class Node 
{
public:
	Node(const T &data);

	T m_data{};
	Node *m_next{};
};

 template<typename T>
Node<T>::Node(const T &data)
	: m_data{ data }, m_next{ nullptr }
{
}
#endif