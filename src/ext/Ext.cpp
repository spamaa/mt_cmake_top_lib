#include "CMakeTopLibSpecificApi.h"

#if defined(CMAKETOPLIB_EXT)
namespace CMekeTopLib
{
    int GiveMeSomeInt()
    {
        return 12345;
    }
}
#endif