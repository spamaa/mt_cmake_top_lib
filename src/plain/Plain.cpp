#include "CMakeTopLibSpecificApi.h"

#if !defined(CMAKETOPLIB_EXT)
namespace CMakeTopLib
{
    char GiveMeSomeChar()
    {
        return 'a';
    }
}
#endif