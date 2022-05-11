// CMaleLibTop.cpp : Defines the entry point for the application.
//

#include "CMakeTopLib.h"
#include "CMakeStaticLib.h"
#include <iostream>


namespace CMakeTopLib
{
	void About()
	{
		::std::cout << "Hello from CMakeLibTop" << ::std::endl;
		::std::cout << __FUNCTION__ << ":" << __FILE__ << ":" << __LINE__ << std::endl;
		::std::cout << "=== 2.1.4 ===" << ::std::endl;
#		if defined (MSVC_ASAN_ENABLED)
		::std::cout << "msvc asan ENABLED" << ::std::endl;
#		else
		::std::cout << "msvc asan DIABLED" << ::std::endl;
#		endif
	}

	void AboutStaticLib()
	{
		::std::cout << "!!!! MESSAGE FROM STATIC LIB - BEGIN !!!!" << ::std::endl;
		::CMakeStaticLib::About();
		::std::cout << "!!!! MESSAGE FROM STATIC LIB - END !!!!" << ::std::endl;
	}
}

