#include "array.h"
#include "array.cpp"
#include <iostream>
#include <string>

namespace SDI_TEST{

	int main()
	{
		int arrSize = NULL;
		std::cout << "Please chose a size for the array: ";
		std::cin >> arrSize;
		std::cout << std::endl;
		Array<int> myArray(arrSize);
		bool run = true;
		while(run)
		{
			std::cout << "Please enter one of the following: " << std::endl;
			std::cout << "1 - Load previous array" << std::endl; 
			std::cout << "2 - Save current array" << std::endl; 
			std::cout << "3 - Write to position" << std::endl; 
			std::cout << "4 - Read from position" << std::endl;
			std::cout << "5 - Double array size" << std::endl;
			std::cout << "6 - Half array size" << std::endl;
			std::cout << "7 - Return size" << std::endl;
			std::cout << "8 - Return current end" << std::endl;
			std::cout << "9 - Run multiple instances example" << std::endl;
			std::cout << "10 - Sort array" << std::endl;
			std::cout << "11 - Search for value" << std::endl;
			std::cout << "12 - Print all" << std::endl;
			std::cout << "13 - Exit" << std::endl << std::endl;
			int userValue = NULL;
			std::cin >> userValue;

			if (userValue == 1) 
				myArray.load();
			else if (userValue == 2) 
				myArray.save();
			else if (userValue == 3)
			{
				int position = NULL;
				int value;
				std::cout << "Please enter a position: ";
				std::cin >> position;
				std::cout << std::endl << "Please enter an integer value to write: ";
				std::cin >> value;
				myArray.writeTo(position, value);
				std::cout << std::endl;
			}
			else if (userValue == 4)
			{
				int position = NULL;
				std::cout << "Please enter a position: ";
				std::cin >> position;
				std::cout << myArray.readFrom(position) << std::endl;
			}
			else if (userValue == 5) 
				myArray.growArray();
			else if (userValue == 6)
				myArray.shrinkArray();
			else if (userValue == 7)
				std::cout << "Size: " << myArray.size() << std::endl << std::endl;
			else if (userValue == 8)
				std::cout << "End: " << myArray.end() << std::endl << std::endl;
			else if (userValue == 9)
			{
				Array<int> instanceOne(5);
				Array<long> instanceTwo(5);

				for (int i = 0; i < instanceOne.size(); i++)
				{
					std::cout << "Writing to " << i << " value " << (i * 2) << " in instance one." << std::endl;
					instanceOne.writeTo(i, (i * 2));
				}
				for (int y = 0; y < instanceOne.size(); y++)
				{
					instanceTwo.writeTo(y, instanceOne.readFrom(y));
					std::cout << "Copied value " << instanceOne.readFrom(y) << " to position " << y << " in instance two." << std::endl;
				}
			}
			else if (userValue == 10)
				myArray.sort();
			else if (userValue == 11)
			{
				std::cout << "Please enter a value: ";
				int value = NULL;
				std::cin >> value;
				if (myArray.search(value))
					std::cout << std::endl << "Value found within array." << std::endl;
				else
					std::cout << std::endl << "Value not found within array." << std::endl;
			}
			else if (userValue == 12)
			{
				for (int i = 0; i < myArray.size(); i++)
					std::cout << myArray.readFrom(i) << ", ";
				std::cout << std::endl;
			}
			else if (userValue == 13)
				run = false;
		}
		return 0;
	}
}