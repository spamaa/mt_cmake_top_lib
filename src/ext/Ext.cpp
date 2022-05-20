#include "CMakeTopLibSpecificApi.h"

#if defined(CMAKETOPLIB_EXT)
namespace CMekTopLib
{
    int GiveMeSomeInt()
    {
        return 12345;
    }
}
#endif