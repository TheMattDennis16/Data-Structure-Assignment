#ifndef LIST_H
#define LIST_H
#include <string>
#include <fstream>
#include <sstream>

namespace SDI_TEST
{
	template <class type> class Node
	{
	public:
		type value;
		Node<type>* previous;
		Node<type>* next;
	};
	template <class type> class List
	{
	private:
		Node<type>* head;
		Node<type>* currentNode;
		bool checkFile(std::string fName);
		int _length;
		
	public:
		List();
		List(List &copy);
		~List();
		bool insertEnd(type value);
		bool remove(int position);
		bool search(type value);
		bool next();
		int end();
		bool previous();
		bool gotoHead();
		bool gotoEnd();
		type readPosition(int position);
		type readCurrent();
		bool writeCurrent(type value);
		bool writeTo(int position, type value);
		bool save();
		bool load();
		bool writeToLog(std::string functName, type value, bool isError = false, std::string errorType = "No error");
		bool sort();
	};
	
}
#endif