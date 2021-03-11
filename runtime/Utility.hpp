#include <stddef.h>

namespace fastscript::runtime::utility
{
    template <typename a>
    size_t arr_length(a* arr[])
    {
        if (sizeof(arr) == 0)
            return 0;
        return sizeof(arr) / sizeof(arr[0]);
    }
}