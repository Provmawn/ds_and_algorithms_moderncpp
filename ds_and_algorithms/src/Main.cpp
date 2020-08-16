#include "CompleteBinaryTree.h"
#include <iostream>

int main() {
	CompleteBinaryTree<int> bt{ 1, 2, 3, 4, 5 };
	std::cout << bt << '\n';
	return 0;
}