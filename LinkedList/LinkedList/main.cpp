#include <iostream>
#include "list.h"
#include "list.cpp"

namespace SDI_TEST
{
	int main()
	{
		List<int> myList;
		while(true)
		{
			std::cout << "Please enter one of the following: " << std::endl;
			std::cout << "1 - Load previous list" << std::endl; 
			std::cout << "2 - Save current list" << std::endl; 
			std::cout << "3 - Write to current position" << std::endl; 
			std::cout << "4 - Read from current position" << std::endl;
			std::cout << "5 - Read specified position" << std::endl;
			std::cout << "6 - Go to start" << std::endl;
			std::cout << "7 - Go to end" << std::endl;
			std::cout << "8 - Go next" << std::endl;
			std::cout << "9 - Go previous" << std::endl;
			std::cout << "10 - Search for value" << std::endl;
			std::cout << "11 - Insert at the end" << std::endl;
			std::cout << "12 - Sort list" << std::endl;
			std::cout << "13 - Exit" << std::endl << std::endl;
			int userValue = NULL;
			std::cin >> userValue;
			
			if (userValue == 1)
				myList.load();
			else if (userValue == 2)
				myList.save();
			else if (userValue == 3)
			{
				int value = 0;
				std::cout << "Please enter a value to enter: ";
				std::cin >> value;
				myList.writeCurrent(value);
				std::cout << std::endl;
			}
			else if (userValue == 4)
				std::cout << "Current value: " << myList.readCurrent() << std::endl;
			else if (userValue == 5)
			{
				int position = 0;
				std::cout << "Please enter the position to insert into: ";
				std::cin >> position;
				std::cout << "Value: " << myList.readPosition(position) << std::endl;
				std::cout << std::endl;
			}
			else if (userValue == 6)
				myList.gotoHead();
			else if (userValue == 7)
				myList.gotoEnd();
			else if (userValue == 8)
				myList.next();
			else if (userValue == 9)
				myList.previous();
			else if (userValue == 10)
			{
				int value = 0;
				std::cout << "Please enter the value to search for: ";
				std::cin >> value;
				if (myList.search(value))
				{
					std::cout << "Value found." << std::endl;
				}
				else
				{
					std::cout << "Value not found." << std::endl;
				}
			}
			else if (userValue == 11)
			{
				std::cout << "Please enter the value to insert: ";
				int value = 0;
				std::cin >> value;
				myList.insertEnd(value);

			}
			else if (userValue == 12)
				myList.sort();
			else if (userValue == 13)
				break;
			else if (userValue == 14)
			{
				myList.gotoHead();
				int currVal = 0;
				while (currVal <= myList.end())
				{
					std::cout << myList.readPosition(currVal) << ", ";
					currVal++;
				}
			}
		}
		return 0;
	}
}