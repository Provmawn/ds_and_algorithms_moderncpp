#ifndef COMPLETEBINARYTREE_H
#define COMPLETEBINARYTREE_H
#include "BinaryTreeNode.h"
#include <initializer_list>
#include <iostream>
template<typename T>
class CompleteBinaryTree 
{
public:
	CompleteBinaryTree();
	CompleteBinaryTree(std::initializer_list<T> list);
	CompleteBinaryTree(T array[], int size);
	~CompleteBinaryTree();

	friend std::ostream& operator<<(std::ostream &out, const CompleteBinaryTree &complete_binary_tree)
	{
		complete_binary_tree.printChildren(out, complete_binary_tree.m_root);
		return out;
	}
private:
	T *m_array{};
	int m_size{};
	BinaryTreeNode<T> *m_root{};

	// recursive helper functions for traversing the tree
	void attachChildren(BinaryTreeNode<T> *parent, int parent_index);
	void printChildren(std::ostream &out, BinaryTreeNode<T> *child) const;
	void deleteChildren(BinaryTreeNode<T> *parent);
};

template<typename T>
CompleteBinaryTree<T>::CompleteBinaryTree()
{

}

template<typename T>
CompleteBinaryTree<T>::CompleteBinaryTree(std::initializer_list<T> list)
	: m_array{ new T[static_cast<int>(list.size())] }, m_size{ static_cast<int>(list.size()) }
{
	int index{ 0 };
	for (const auto &element : list) {
		m_array[index] = element;
		++index;
	}
	m_root = new BinaryTreeNode<T>{ m_array[0] };
	attachChildren(m_root, 0);
}

template<typename T>
CompleteBinaryTree<T>::CompleteBinaryTree(T array[], int size)
	: m_array{ new T[size] }, m_size{ size }
{
	for (int i{ 0 }; i < m_size; ++i)
		m_array[i] = array[i];
	m_root = new BinaryTreeNode<T>{ m_array[0] };
	attachChildren(m_root, 0);
}

template<typename T>
CompleteBinaryTree<T>::~CompleteBinaryTree()
{
	deleteChildren(m_root);
	delete[] m_array;
}

template<typename T>
void CompleteBinaryTree<T>::attachChildren(BinaryTreeNode<T> *parent, int parent_index)
{
	if (parent_index >= m_size)
		return;

	int left_index{ 2 * parent_index + 1 };
	int right_index{ 2 * parent_index + 2 };

	if (left_index < m_size)
		parent->m_left = new BinaryTreeNode<T>{ m_array[left_index] };
	if (right_index < m_size)
		parent->m_right = new BinaryTreeNode<T>{ m_array[right_index] };

	attachChildren(parent->m_left, left_index);
	attachChildren(parent->m_right, right_index);
}

template<typename T>
void CompleteBinaryTree<T>::printChildren(std::ostream &out, BinaryTreeNode<T> *node) const
{
	out << node->m_data << ' ';
	if (node->m_left)
		printChildren(out, node->m_left);
	if (node->m_right)
		printChildren(out, node->m_right);
}

template<typename T>
void CompleteBinaryTree<T>::deleteChildren(BinaryTreeNode<T> *parent)
{
	if (parent->m_left)
		deleteChildren(parent->m_left);
	if (parent->m_right)
		deleteChildren(parent->m_right);
	delete parent;
}
#endif