// CMaleLibTop.cpp : Defines the entry point for the application.
//

#include "CMakeTopLib.h"
#include "CMakeStaticLib.h"
#include <iostream>
#include <fmt/format.h>


namespace CMakeTopLib
{
	void About()
	{
		::std::cout << "Hello from CMakeLibTop" << ::std::endl;
		::std::cout << __FUNCTION__ << ":" << __FILE__ << ":" << __LINE__ << std::endl;
		::std::cout << "=== 2.8.0 ===" << ::std::endl;
#		if defined (MSVC_ASAN_ENABLED)
		::std::cout << "msvc asan ENABLED" << ::std::endl;
#		else
		::std::cout << "msvc asan DIABLED" << ::std::endl;
#		endif
#		if defined (CMAKETOPLIB_EXT)
		::std::cout << "Extended library version" << ::std::endl;
#		else
		::std::cout << "Standard library version" << ::std::endl;
#		endif
	}

	void AboutStaticLib()
	{
		::std::cout << "!!!! MESSAGE FROM STATIC LIB - BEGIN !!!!" << ::std::endl;
		::CMakeStaticLib::About();
		::std::cout << "!!!! MESSAGE FROM STATIC LIB - END !!!!" << ::std::endl;
	}

	void MakeMemError()
	{
		int aa[] = { 0, 1 };
		::std::cout << "!!!! Making ASAN error in lib: '" << aa[2] << "'" << ::std::endl;
	}

	bool IsExtendedLib()
	{
#	if defined (CMAKETOPLIB_EXT)
		return true;
#	else
		return false;
#	endif
	}

	void MessageFromFmt()
	{
		::fmt::print("Message from fmt lib: {}:{}", __FILE__, __LINE__);
	}
}

