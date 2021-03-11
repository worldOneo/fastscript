#pragma once
#include <stddef.h>
#include "Variables/Variable.hpp"

namespace fastscript::runtime::utility
{
    typedef int (*_math_operator)(int, int);

    template <typename a>
    size_t arr_length(a *arr[])
    {
        if (sizeof(arr) == 0)
            return 0;
        return sizeof(arr) / sizeof(arr[0]);
    }

    int _math_operation(MathVar *var1, Variable *var2, _math_operator oper);

    int _math_xor(int a, int b);
    int _math_or(int a, int b);
    int _math_and(int a, int b);
    int _math_rshft(int a, int b);
    int _math_lshft(int a, int b);

    int _math_eq(int a, int b);
    int _math_gt(int a, int b);
    int _math_lt(int a, int b);

    int _math_add(int a, int b);
    int _math_subtract(int a, int b);
    int _math_divide(int a, int b);
    int _math_multiply(int a, int b);
}