// CMaleLibTop.cpp : Defines the entry point for the application.
//

#include "CMakeLibTop.h"
#include <iostream>


namespace CMakeLibTop
{
	void About()
	{
		::std::cout << "Hello from CMakeLibTop" << ::std::endl;
		::std::cout << __FUNCTION__ << ":" << __FILE__ << ":" << __LINE__ << std::endl;
		::std::cout << "=== 1.0.4 ===" << ::std::endl;
		::std::cout << "This is some master change 00" << ::std::endl;
	}
}

