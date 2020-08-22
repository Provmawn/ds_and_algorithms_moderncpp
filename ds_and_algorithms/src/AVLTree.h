#ifndef AVLTREE_H
#define AVLTREE_H
#include "IAVLTree.h"
#include "AVLNode.h"
#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <memory>
template<typename T>
class AVLTree : public IAVLTree<T>
{
public:
	using nodeptr_t = std::unique_ptr<AVLNode<T>>;
	AVLTree(std::initializer_list<T> list);
	virtual ~AVLTree();
	virtual void insert(const T &data) override;
	virtual void remove(const T &data) override;

	friend std::ostream& operator<<(std::ostream &out, const AVLTree &avl_tree)
	{
		avl_tree.inorderPrint(out, avl_tree.m_root);
		return out;
	}

private:
	nodeptr_t m_root{};

	void recursiveInsert(nodeptr_t &node, const T &data);
	void inorderPrint(std::ostream &out, const nodeptr_t &node) const;
	int calculateHeight(const nodeptr_t &node) const;
	int calculateBalance(const nodeptr_t &node) const;
	void leftRotate(nodeptr_t &root);
	void rightRotate(nodeptr_t &root);
};

template<typename T>
AVLTree<T>::AVLTree(std::initializer_list<T> list)
	: m_root{ nullptr }
{
}

template<typename T>
AVLTree<T>::~AVLTree()
{
}

template<typename T>
void AVLTree<T>::insert(const T &data)
{
	if (!m_root)
	{
		m_root = std::make_unique<AVLNode<T>>(data);
		return;
	}
	recursiveInsert(m_root, data);
}

template<typename T>
void AVLTree<T>::remove(const T &data)
{

}

template<typename T>
void AVLTree<T>::recursiveInsert(nodeptr_t &node, const T &data)
{
	if (data > node->m_data)
	{
		if (node->m_right)
			recursiveInsert(node->m_right, data);
		else
			node->m_right = std::make_unique<AVLNode<T>>(data);
	}
	else
	{
		if (node->m_left)
			recursiveInsert(node->m_left, data);
		else
			node->m_left = std::make_unique<AVLNode<T>>(data);
	}

	int balance{ calculateBalance(node) };

	// right subtree height > left subtree height
	if (balance < -1)
	{
		// left left case
		if (data > node->m_right->m_data)
			leftRotate(node);
		else if (data < node->m_right->m_data)
		{
			rightRotate(node->m_right);
			leftRotate(node);
		}
	}
	// left subtree height > right subtree height
	else if (balance > 1)
	{
		// right right case
		if (data < node->m_left->m_data)
			rightRotate(node);
		// left right case
		else if (data > node->m_left->m_data)
		{
			leftRotate(node->m_left);
			rightRotate(node);
		}
	}
}

template<typename T>
void AVLTree<T>::inorderPrint(std::ostream &out, const nodeptr_t &node) const
{
	if (node->m_left)
		inorderPrint(out, node->m_left);
	out << "node(" << node->m_data << ", " << calculateHeight(node) - 1 << ")\n";
	if (node->m_right)
		inorderPrint(out, node->m_right);
}

template<typename T>
int AVLTree<T>::calculateHeight(const nodeptr_t &node) const
{
	if (!node->m_left && !node->m_right)
		return 1;
	if (node->m_left && node->m_right)
		return 1 + std::max<int>(calculateHeight(node->m_left), calculateHeight(node->m_right));
	if (node->m_left)
		return 1 + calculateHeight(node->m_left);
	if (node->m_right)
		return 1 + calculateHeight(node->m_right);

}

template<typename T>
int AVLTree<T>::calculateBalance(const nodeptr_t &node) const
{
	if (node->m_left && node->m_right)
		return calculateHeight(node->m_left) - calculateHeight(node->m_right);
	if (node->m_left)
		return calculateHeight(node->m_left);
	if (node->m_right)
		return -calculateHeight(node->m_right);

	// if no children then balance is 0
	return 0;
}

template<typename T>
void AVLTree<T>::leftRotate(nodeptr_t &root)
{

	nodeptr_t parent{ std::move(root->m_right) };
	root->m_right = std::move(parent->m_left);
	parent->m_left = std::move(root);

	root = std::move(parent);
}

template<typename T>
void AVLTree<T>::rightRotate(nodeptr_t &root)
{
	nodeptr_t parent{ std::move(root->m_left) };
	root->m_left = std::move(parent->m_right);
	parent->m_right = std::move(root);

	root = std::move(parent);
}
#endif