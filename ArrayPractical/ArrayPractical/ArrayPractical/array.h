#ifndef ARRAY_H
#define ARRAY_H
#include <string>

namespace SDI_TEST
{
	template <class type> class Array
	{
	private:
		type* ourArray;
		int _size;
		bool checkFile(std::string fName);
	public:
		Array(int size);//
		~Array();
		Array(const Array &copy);
		type readFrom(int position); //
		bool writeTo(int position, type value); //
		bool load(); //
		bool save(); //
		int size();
		int end();
		bool growArray();
		bool shrinkArray();
		bool sort();
		bool search(type value);
		bool writeToLog(std::string functName, type value, bool isError = false, std::string errorType = "No error");
	};
}
#endif