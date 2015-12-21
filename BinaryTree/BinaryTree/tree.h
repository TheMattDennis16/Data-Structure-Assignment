#ifndef TREE_H
#define TREE_H
typedef int StoredData;
#include <iostream>
#include <fstream>
#include <sstream>
namespace SDI 
{
	class Node 
	{
	public:
		Node* lNode;
		Node* rNode;
		Node* pNode;
		StoredData value;
	};

	class Tree
	{
	private:
		Node* head;
		Node* currentNode;
		bool checkFile(std::string fName);
		bool _search(StoredData value, Node* rootNode);
		bool _insertNode(StoredData value, Node* leaf);
		int _countNodes(Node* rootNode);
		void _print(Node* currNode);
		bool _delete(StoredData value, Node* currNode);

	public:
		Tree();
		Tree(Tree &copy);
		~Tree();
		bool writeToLog(std::string functType, StoredData value, bool isError = false, std::string errorType = "No error found");
		bool search(StoredData value);
		bool goHead();
		bool setPos(int direction);
		bool insertNode(StoredData value);
		void print();
		StoredData readCurrent();
		int size();
		bool deleteNode(StoredData value);
	};
}
#endif