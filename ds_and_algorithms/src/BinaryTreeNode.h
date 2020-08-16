#ifndef BINARYTREENODE_H
#define BINARYTREENODE_H
template<typename T>
class BinaryTreeNode 
{
public:
	BinaryTreeNode() = default;
	BinaryTreeNode(const T &data);

	T m_data{};
	BinaryTreeNode *m_left{};
	BinaryTreeNode *m_right{};
};

template<typename T>
BinaryTreeNode<T>::BinaryTreeNode(const T &data)
	: m_data{ data }, m_left{ nullptr }, m_right{ nullptr }
{
}
#endif