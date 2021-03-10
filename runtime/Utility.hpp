#include <stddef.h>

namespace fastscript::runtime::utility
{
    template <typename a>
    size_t arr_length(a[])
    {
        if (sizeof(a) == 0)
            return 0;
        return sizeof(a) / sizeof(a[0]);
    }
}