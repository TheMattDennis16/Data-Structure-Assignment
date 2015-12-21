#include <string>
#include <fstream>
#include <sstream>

namespace SDI_TEST
{
	template <class type> 
	SDI_TEST::Array<type>::Array(int size)
	{
		if (size == NULL)
		{
			size = 10;
		}
		else if (size > 32768)
		{
			size = 32767;
		}
		ourArray = new type[size];
		writeToLog("Constructor ", 0);
		_size = size;
	}
	template <class type> 
	SDI_TEST::Array<type>::~Array()
	{
		delete[] ourArray;
		writeToLog("Deconstructor ", 0);
	}
	template <class type> 
	SDI_TEST::Array<type>::Array(const Array<type> &copy)
	{
		ourArray = new type[(_size*2)];
		*ourArray = *copy.ourArray;
		writeToLog("Copy ", 0);
	}
	template <class type> 
	type SDI_TEST::Array<type>::readFrom(int position)
	{
		if (position < _size)
		{
			
			writeToLog("Read ", ourArray[position]);
			return ourArray[position];
		}
		writeToLog("Read ", NULL, true,"Position exceded bounds of array.");
		return NULL;
	}
	template <class type> 
	int SDI_TEST::Array<type>::size()
	{
		return _size;
	}
	template <class type> 
	int SDI_TEST::Array<type>::end()
	{
		int endVal = NULL;
		if (ourArray[0] == -858993460)
			return NULL;
		for (int i = 0; i < _size; i++)
		{
			if (ourArray[i+1] != -858993460)
			{
				endVal = i;
			}
		}
		return endVal;
	}
	template <class type>
	bool SDI_TEST::Array<type>::writeTo(int position, type value)
	{
		if (position < _size)
		{
			ourArray[position] = value;
			writeToLog("Wrote ", value);
			return true;
		}
		writeToLog("Wrote ", value, true, "Position excedes size of Array.");
		return false;
	}
	template <class type> 
	bool SDI_TEST::Array<type>::save()
	{
		checkFile("backup.csv");
		std::fstream file;
		file.open("backup.csv", std::fstream::out);
		if (file.is_open())
		{
			int currVal = 0;
			int endVal = end();
			while (currVal < (endVal+1))
			{
				file << ourArray[currVal] << ",";
				currVal++;
			}
			file << "\n";
			file.close();
			writeToLog("Saving ", currVal);
			return true;
		}
		writeToLog("Saving ", NULL, true, "File not found.");
		return false;
	}
	template <class type> 
	bool SDI_TEST::Array<type>::load()
	{
		checkFile("backup.csv");
		std::ifstream file;
		file.open("backup.csv", std::fstream::in);
		if (file.is_open())
		{
			int position = 0;
			std::string currLine = "";
			getline(file, currLine);
			std::stringstream strStream(currLine);
			std::string item = "";
			while (getline(strStream, item, ','))
			{
				if (position < _size)
				{
					if (atoi(item.c_str()) != -842150451)
					{
						ourArray[position] = atoi(item.c_str());
						position++;
					}
				}
				else
				{
					break;
				}
			}
			writeToLog("Loading ", position);
			return true;
		}
		writeToLog("Loading", NULL, true, "File not found.");
		return false;
	}
	template <class type> 
	bool SDI_TEST::Array<type>::growArray()
	{
		int arrSize = _size;
		_size = _size * 2;
		type* tempArr = new type[_size];
		for (int i = 0; i < _size; i++)
			tempArr[i] = ourArray[i];
		delete[] ourArray;
		ourArray = tempArr;
		writeToLog("Grew array ", arrSize);
		return true;
	}
	template <class type> 
	bool SDI_TEST::Array<type>::shrinkArray()
	{
		int arrSize = _size;
		_size = _size / 2;
		if (_size >= 1)
		{
			type* tempArr = new type[_size];
			for (int i = 0; i < _size; i++)
				tempArr[i] = ourArray[i];
			delete[] ourArray;
			ourArray = tempArr;
			writeToLog("Shrunk array ", arrSize);
			return true;
		}
		return false;
	}
	template <class type> 
	bool SDI_TEST::Array<type>::checkFile(std::string fName)
	{
		std::fstream openF;
		openF.open(fName.c_str(), std::ios::in);
		if(openF.is_open() == false)
		{
			std::ofstream makeF(fName.c_str());
			makeF.close();
		}
		openF.close();
		return true;
	}
	template <class type> 
	bool SDI_TEST::Array<type>::sort()
	{
		int i, j, flag = 1;
		type currVar;
		for (i = 1; (i <= _size) && flag; i++)
		{
			flag = 0;
			for (j = 0; j < (_size - 1); j++)
			{
				if(ourArray[j+1] > ourArray[j])
				{
					currVar = ourArray[j];
					ourArray[j] = ourArray[j+1];
					ourArray[j+1] = currVar;
					flag = 1;
				}
			}
		}
		writeToLog("Sorted array ", NULL);
		return true;
	}
	template <class type> 
	bool SDI_TEST::Array<type>::search(type value)
	{
		for(int i = 0; i < _size; i++)
		{
			if (ourArray[i] == value)
			{
				return true;
				writeToLog("Search ", value);
			}
		}
		writeToLog("Value not found ", NULL);
		return false;
	}
	template <class type>
	bool SDI_TEST::Array<type>::writeToLog(std::string functName, type value, bool isError, std::string errorType)
	{
		checkFile("log.txt");
		std::fstream file;
		file.open("log.txt", std::fstream::out | std::fstream::app);
		if (file.is_open())
		{

			if (isError == true)
			{
				file << "Error found in function: " << functName << " - Value: "
					<< value << " Error type: " << errorType << "\n";
			}
			else
			{
				file << "Function: " << functName << " - Value: "
					<< value << "\n";
			}
			if (functName == "Deconstructor ")
				file << std::endl;
			file.close();
			return true;
		}
		return false;
	}
}
