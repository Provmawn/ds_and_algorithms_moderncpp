#ifndef AVLNODE_H
#define AVLNODE_H
#include <memory>
template<typename T>
class AVLNode
{
public:
	AVLNode(const T &data, int height = 0);
	T m_data{};
	int m_height{};
	std::unique_ptr<AVLNode> m_left{};
	std::unique_ptr<AVLNode> m_right{};

	AVLNode& operator=(const AVLNode &avl_node);
};

template<typename T>
AVLNode<T>::AVLNode(const T &data, int height)
	: m_data{ data }
	, m_height{ height }
	, m_left{ nullptr }
	, m_right{ nullptr }
{
}

template<typename T>
AVLNode<T>& AVLNode<T>::operator=(const AVLNode<T> &avl_node)
{
	m_data = avl_node.m_data;
	m_height = avl_node.m_height;
	return *this;
}
#endif