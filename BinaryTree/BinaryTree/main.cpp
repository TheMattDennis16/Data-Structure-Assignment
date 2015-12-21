#include "tree.h"

int main()
{
	SDI::Tree tree;
	tree.insertNode(5);
	tree.insertNode(7);
	tree.insertNode(3);
	tree.deleteNode(5);
	//tree.print();
	int count = tree.size();
	bool t1 = tree.search(3);
	return 0;
}