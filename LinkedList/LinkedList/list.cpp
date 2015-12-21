
#include <fstream>
#include <sstream>

namespace SDI_TEST
{
	template <class type> 
	SDI_TEST::List<type>::List()
	{
		head = new Node<type>;
		currentNode = new Node<type>;
		head->previous = nullptr;
		head->next = nullptr;
		head->value = NULL;
		currentNode = head;
		_length = 1;
	}
	template <class type> 
	SDI_TEST::List<type>::~List()
	{
		currentNode = head;
		while (currentNode != NULL)
		{
			Node<type>* next = currentNode->next;
			delete currentNode;
			currentNode = next;
		}
		head = 0;
	}
	template <class type> 
	type SDI_TEST::List<type>::readPosition(int position)
	{
		currentNode = head;
		for (int i = 0; i < position; i++)
		{
			if (currentNode->next == nullptr)
				return 0;
			else
				currentNode = currentNode->next;
		}
		return currentNode->value;
	}
	template <class type> 
	type SDI_TEST::List<type>::readCurrent()
	{
		if (currentNode != nullptr)
			return currentNode->value;
		else
			return 0;
	}
	template <class type> 
	bool SDI_TEST::List<type>::insertEnd(type value)
	{
		if (head->value == 0)
		{
			head->value = value;
			return true;
		}
		currentNode = head;
		while (currentNode->next != nullptr)
			currentNode = currentNode->next;
		Node<type>* newNode = new Node<type>();
		newNode->value = value;
		newNode->next = nullptr;
		newNode->previous = currentNode;
		currentNode->next = newNode;
		_length++;
		return true;
	}
	template <class type> 
	bool SDI_TEST::List<type>::writeCurrent(type value)
	{
		if (currentNode != nullptr)
		{
			currentNode->value = value;
			return true;
		}
		return false;
	}
	template <class type> 
	bool SDI_TEST::List<type>::search(type value)
	{
		currentNode = head;
		while (currentNode != nullptr)
		{
			if (currentNode->value == value)
			{
				return true;
			}
			currentNode = currentNode->next;
		}
		return false;
	}
	template <class type> 
	bool SDI_TEST::List<type>::remove(int position)
	{
		currentNode = head;
		if (position == 0)
		{
			head->value == 0;
			return true;
		}
		int counter = 0;
		while (currentNode != nullptr)
		{
			if (counter == position)
			{
				Node* localNode = currentNode;
				currentNode = currentNode->previous;
				currentNode->next = currentNode->next->next;
				currentNode = currentNode->next;
				currentNode->previous = currentNode->previous->previous;
				delete localNode;
				_length--;
				return true;
			}
			counter++;
			currentNode = currentNode->next;
		}
		return false;
	}
	template <class type> 
	bool SDI_TEST::List<type>::next()
	{
		if (currentNode->next != nullptr)
		{
			currentNode = currentNode->next;
		}
		writeToLog("Moved next ", NULL);
		return true;
	}
	template <class type> 
	bool SDI_TEST::List<type>::previous()
	{
		if (currentNode->previous != nullptr)
		{
			currentNode = currentNode->previous;
			return true;
		}
		writeToLog("Moved previous ", NULL);
		return false;
	}
	template <class type> 
	bool SDI_TEST::List<type>::gotoHead()
	{
		if (currentNode != head)
		{
			currentNode = head;
		}
		writeToLog("Go to head", NULL);
		return true;
	}
	template <class type> 
	bool SDI_TEST::List<type>::gotoEnd()
	{
		while (currentNode->next != nullptr)
		{
			currentNode = currentNode->next;
		}
		writeToLog("Go to end ", NULL);
		return true;
	}
	template <class type> 
	bool SDI_TEST::List<type>::save()
	{
		checkFile("backup.csv");
		std::fstream file;
		file.open("backup.csv", std::fstream::out);
		if (file.is_open())
		{
			currentNode = head;
			while (currentNode != nullptr)
			{
				file << currentNode->value << ",";
				currentNode = currentNode->next;
			}
			file << std::endl;
			file.close();
			writeToLog("Saving ", NULL);
			return true;
		}
		writeToLog("Saving ", NULL, true, "File could not be opened.");
		return false;
	}
	template <class type> 
	bool SDI_TEST::List<type>::load()
	{
		checkFile("backup.csv");
		std::ifstream file;
		file.open("backup.csv", std::fstream::in);
		if (file.is_open())
		{
			std::string currLine = "";
			getline(file, currLine);
			std::stringstream strStream(currLine);
			std::string item = "";
			while (getline(strStream, item, ','))
			{
				insertEnd(atoi(item.c_str()));
				writeToLog("Loading ", atoi(item.c_str()));
			}
			return true;
		}
		writeToLog("Loading", NULL, true, "File not found.");
		return false;
	}
	template <class type> 
	bool SDI_TEST::List<type>::writeToLog(std::string functType, type value, bool isError, std::string errorType)
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
	template <class type> 
	bool SDI_TEST::List<type>::checkFile(std::string fName)
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
	template <class type>
	bool SDI_TEST::List<type>::writeTo(int position, type value)
	{
		currentNode = head;
		for (int i = 0; i < _length; i++)
		{
			if (i == position)
			{
				currentNode->value = value;
			}
			currentNode = currentNode->next;
		}
		return false;
	}
	template <class type>
	int SDI_TEST::List<type>::end()
	{
		return _length;
	}
	template <class type>
	bool SDI_TEST::List<type>::sort()
	{
		int i, j, flag = 1;
		type currVal;
		for (i = 1; (i <= _length) && flag; i++)
		{
			flag = 0;
			for (j = 0; j < (_length - 1); j++)
			{
				if (readPosition(j + 1) > readPosition(j))
				{
					currVal = readPosition(j);
					writeTo(j, readPosition(j + 1));
					writeTo(j + 1, currVal);
					flag = 1;
				}
			}
		}
		return true;
	}
}
