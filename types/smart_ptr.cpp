
#include"smart_ptr.hpp"
#include<iostream>
// todo - move this to another location, its own sort of file, and allow custom definition //

namespace boost
{
	void assertion_failed(char const * expr, char const * function, char const * file, long line)
	{
		std::cout << "boost assertion failed:\t "<<  expr << ", in " << file << ", on line " << line << std::endl;
		std::cin.get ();
	}
}
