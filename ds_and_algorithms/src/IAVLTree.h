#ifndef IAVLTREE_H
#define IAVLTREE_H
template<typename T>
class IAVLTree
{
public:
	virtual ~IAVLTree() = default;
	virtual void insert(const T &data) = 0;
	virtual void remove(const T &data) = 0;
};

#endif