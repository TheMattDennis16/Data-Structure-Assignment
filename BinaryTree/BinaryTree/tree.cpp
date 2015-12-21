#ifndef binaryTree_cpp
#define binaryTree_cpp
#include "tree.h"

namespace SDI 
{
	SDI::Tree::Tree()
	{
		head = new Node;
		head->pNode = nullptr;
		head->lNode = nullptr;
		head->rNode = nullptr;
		head->value = NULL;
		currentNode = new Node;
		currentNode = head;
	}
	SDI::Tree::~Tree()
	{
		delete[] head;
	}
	bool SDI::Tree::goHead()
	{
		currentNode = head;
		return true;
	}
	bool SDI::Tree::setPos(int direction)
	{
		if (direction == 0) //Go to parent
		{
			if (currentNode->pNode != nullptr)
			{
				currentNode = currentNode->pNode;
				return true;
			}
		}
		else if (direction == 1) //Go left
		{
			if (currentNode->lNode != nullptr)
			{
				currentNode = currentNode->lNode;
				return true;
			}
		}
		else if (direction == 2) //Go right
		{
			if (currentNode->rNode != nullptr)
			{
				currentNode = currentNode->rNode;
				return true;
			}
		}
		return false;
	}
	StoredData SDI::Tree::readCurrent()
	{
		if (currentNode != nullptr)
		{
			StoredData val = currentNode->value;
			writeToLog("Read current ", val);
			return val;
		}
		else
		{
			writeToLog("Read current ", NULL, true, "No initialised value");
			return 0;
		}
	}
	int SDI::Tree::_countNodes(Node* currNode)
	{
		if (currNode == nullptr)
			return 0;
		else
		{
			int count = 1;
			count += _countNodes(currNode->lNode);
			count += _countNodes(currNode->rNode);
			return count;
		}
	}
	int SDI::Tree::size()
	{
		int count = _countNodes(head);
		writeToLog("Counted ", count);
		return count;
	}
	bool SDI::Tree::insertNode(StoredData value)
	{
		if (_insertNode(value, head))
		{
			writeToLog("Inserted ", value);
			return true;
		}
		writeToLog("inserted ", value, true, "Could not insert");
		return false;
	}
	bool SDI::Tree::_insertNode(StoredData value, Node* currNode)
	{
		if (head->value == 0)
		{
			head->value = value;
			return true;
		}
		if (value < currNode->value)
		{
			if (currentNode->lNode != nullptr)
				_insertNode(value, currNode->lNode);
			else
			{
				currNode->lNode = new Node;
				currNode->lNode->lNode = nullptr;
				currNode->lNode->rNode = nullptr;
				currNode->lNode->pNode = nullptr;
				currNode->lNode->value = value;
			}
		}
		else if (value >= currNode->value)
		{
			if (currNode->rNode != nullptr)
				_insertNode(value, currNode->rNode);
			else
			{
				currNode->rNode = new Node;
				currNode->rNode->lNode = nullptr;
				currNode->rNode->rNode = nullptr;
				currNode->rNode->pNode = nullptr;
				currNode->rNode->value = value;
			}
		}
		return false;
	}
	bool SDI::Tree::_search(StoredData value, Node* currNode)
	{
		if(currNode != nullptr)
		{
			if(value == currNode->value)
				return true;

			if(value < currNode->value)
				return _search(value, currNode->lNode);
			else
				return _search(value, currNode->rNode);
		}
		return false;
	}
	bool SDI::Tree::search(StoredData value)
	{
		if (_search(value, head))
		{
			writeToLog("Searched for ", value);
			return true;
		}
		writeToLog("Searched for ", value, true, "Value not found.");
		return false;
	}
	void SDI::Tree::print()
	{
		_print(head);
	}
	void SDI::Tree::_print(Node* currNode)
	{
		if(currNode->value != 0)
		{
			std::cout << currNode->value << ", ";
			writeToLog("Printed value ", currNode->value);
			_print(currentNode->lNode); 
			_print(currentNode->rNode);
		}
	}
	bool SDI::Tree::checkFile(std::string fName)
	{
		std::fstream openF;
		openF.open(fName.c_str(), std::ios::in);
		if (openF.is_open() == false)
		{
			std::ofstream makeF(fName.c_str());
			makeF.close();
		}
		openF.close();
		return true;
	}
	bool SDI::Tree::writeToLog(std::string functType, StoredData value, bool isError, std::string errorType)
	{
		checkFile("log.txt");
		std::fstream file;
		file.open("log.txt", std::fstream::out | std::fstream::app);
		if (file.is_open())
		{
			if (isError == true)
			{
				file << "Error found in function: " << functType << " - Value: "
					<< value << " Error type: " << errorType << "\n";
			}
			else
			{
				file << "Function: " << functType << " - Value: "
					<< value << "\n";
			}
			if (functType == "Deconstructor ")
				file << std::endl;
			file.close();
			return true;
		}
		return false;
	}
	bool SDI::Tree::deleteNode(StoredData value)
	{
		if(_delete(value, head))
		{
			writeToLog("Delete ", value);
			return true;
		}
		return false;
	}
	bool SDI::Tree::_delete(StoredData value, Node* currNode)
	{
		if (head == nullptr)
			return false;
		Node* parent = nullptr;

		if(search(value))
		{
			if(currNode == nullptr)
				return false;

			/* No child node */
			if(currNode->lNode == nullptr && currNode->rNode == nullptr)
			{
				if(parent->lNode == currNode)
					parent->lNode = nullptr;
				else
					parent->rNode = nullptr;
				delete currNode;
				return true;
			}

			/* One child node */
			if((currNode->lNode != nullptr &&  currNode->rNode == nullptr) || (currNode->lNode == nullptr &&  currNode->rNode != nullptr))
			{
				if (currNode->lNode != nullptr &&  currNode->rNode == nullptr)
				{
					if(parent->lNode == currNode)
						parent->lNode = currNode->rNode;
					else
						parent->rNode = currNode->rNode;
				}
				else
				{
					if(parent->lNode == currNode)
						parent->lNode = currNode->lNode;
					else
						parent->rNode = currNode->lNode;
				}
				delete currNode;
				return true;
			}

			/* Two child nodes */
			if(currNode->lNode != nullptr && currNode->rNode != nullptr)
			{
				Node* right = currNode->rNode;
				if(right->lNode == nullptr && right->rNode == nullptr)
				{
					currNode->value = right->value;
					delete right;
					currNode->rNode = nullptr;
				}
				else
				{
					if((currNode->rNode)->lNode != nullptr)
					{
						Node* left;
						Node* leftParent;
						leftParent = currNode->rNode;
						left = (currNode->rNode)->lNode;
						while(left->lNode != nullptr)
						{
							leftParent = left;
							left = left->lNode;
						}
						currNode->value = left->value;
						delete left;
						leftParent->lNode = nullptr;
					}
					else
					{
						right = currNode->rNode;
						currNode->value = right->value;
						currNode->rNode = right->rNode;
						delete right;
					}
				}
			}
		}
		return false;
	}
}
#endif