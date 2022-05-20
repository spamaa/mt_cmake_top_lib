#pragma once

namespace CMakeTopLib
{

#   if defined (CMAKETOPLIB_EXT)
    int GiveMeSomeInt();
#   else
    char GiveMeSomeChar();
#   endif
}