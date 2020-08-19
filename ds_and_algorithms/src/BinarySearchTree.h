#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "BinaryTreeNode.h"
#include "BSTException.h"
#include <initializer_list>
#include <iostream>

template<typename T>
class BinarySearchTree
{
public:
	BinarySearchTree() = delete;
	BinarySearchTree(std::initializer_list<T> list);

	void insert(const T &data);
	void remove(const T &data);

	friend std::ostream& operator<<(std::ostream &out, const BinarySearchTree &bst)
	{
		bst.inorderPrint(bst.m_root, out);
		return out;
	}

private:
	BinaryTreeNode<T> *m_root{};
	int m_size{};

	void attachNode(BinaryTreeNode<T> *node, const T &data);
	void insertNode(BinaryTreeNode<T> *node, const T &data);
	void removeNode(BinaryTreeNode<T> *node, const T &data);
	BinaryTreeNode<T>* findMinNode(BinaryTreeNode<T> *node);
	void inorderPrint(BinaryTreeNode<T> *node, std::ostream &out) const;
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree(std::initializer_list<T> list)
{

	int index{ 0 };
	constexpr int first{ 0 };
	for (const auto &element : list)
	{
		if (index == first)
			m_root = new BinaryTreeNode<T>{ element };
		else 
			attachNode(m_root, element);
		++index;
	}
}

template<typename T>
void BinarySearchTree<T>::insert(const T &data)
{
	insertNode(m_root, data);
}

template<typename T>
void BinarySearchTree<T>::remove(const T &data)
{
	removeNode(m_root, data);
}

template<typename T>
void BinarySearchTree<T>::removeNode(BinaryTreeNode<T> *node, const T &data)
{

	if (data > node->m_data)
	{
		if (node->m_right)
			removeNode(node->m_right, data);
		else
			throw BSTException("Node not in tree");
			// node not in tree
	}
	else if (data < node->m_data)
	{
		if (node->m_left)
			removeNode(node->m_left, data);
		else
			throw BSTException("Node not in tree");
	}
	else if (data == node->m_data)	// found node
	{
		// leaf node
		if (!node->m_right && !node->m_left)
		{
			delete node;
			node == nullptr;
		}
		// two children
		else if (node->m_right && node->m_left)
		{
			BinaryTreeNode<T> *replacement{ findMinNode(node->m_right) };
			node->m_data = replacement->m_data;
			delete replacement;
			replacement = nullptr;
		}
		// one child
		else if (node->m_right)
		{
			node->m_data = node->m_right->m_data;
			delete node->m_right;
			node->m_right = nullptr;
		}
		else if (node->m_left)
		{
			node->m_data = node->m_left->m_data;
			delete node->m_left;
			node->m_left = nullptr;
		}
	}
}

template<typename T>
BinaryTreeNode<T>* BinarySearchTree<T>::findMinNode(BinaryTreeNode<T> *node)
{
	BinaryTreeNode<T> *leftist{ node };

	while (leftist->m_left)
		leftist = leftist->m_left;

	return leftist;
}

template<typename T>
void BinarySearchTree<T>::insertNode(BinaryTreeNode<T> *node, const T &data)
{

	if (data > node->m_data)
	{
		if (node->m_right)
			insertNode(node->m_right, data);
		else
			node->m_right = new BinaryTreeNode<T>{ data };
	}
	else if (data <= node->m_data) 
	{
		if (node->m_left)
			insertNode(node->m_left, data);
		else
			node->m_left = new BinaryTreeNode<T>{ data };
	}
}

template<typename T>
void BinarySearchTree<T>::attachNode(BinaryTreeNode<T> *node, const T &data)
{
	if (data > node->m_data)
	{
		if (node->m_right)
			attachNode(node->m_right, data);
		else
			node->m_right = new BinaryTreeNode<T>{ data };
	}
	else if (data <= node->m_data)
	{
		if (node->m_left)
			attachNode(node->m_left, data);
		else
			node->m_left = new BinaryTreeNode<T>{ data };
	}
}

template<typename T>
void BinarySearchTree<T>::inorderPrint(BinaryTreeNode<T> *node, std::ostream &out) const
{
	if (node->m_left)
		inorderPrint(node->m_left, out);

	out << node->m_data << ' ';

	if (node->m_right)
		inorderPrint(node->m_right, out);
}
#endif