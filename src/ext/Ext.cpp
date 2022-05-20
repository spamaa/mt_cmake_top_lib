#include "CMakeTopLibSpecificApi.h"

#if defined(CMAKETOPLIB_EXT)
namespace CMakeTopLib
{
    int GiveMeSomeInt()
    {
        return 12345;
    }
}
#endif