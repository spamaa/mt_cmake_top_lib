// CMaleLibTop.cpp : Defines the entry point for the application.
//

#include "CMakeTopLib.h"
#include <iostream>


namespace CMakeTopLib
{
	void About()
	{
		::std::cout << "Hello from CMakeLibTop" << ::std::endl;
		::std::cout << __FUNCTION__ << ":" << __FILE__ << ":" << __LINE__ << std::endl;
		::std::cout << "=== 2.0.0 ===" << ::std::endl;
	}
}

