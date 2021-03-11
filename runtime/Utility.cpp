#include "Utility.hpp"
#include "iostream"

namespace fastscript::runtime::utility
{
    Integer *_math_operation(MathVar *var1, Variable *var2, _math_operator oper)
    {
        MathVar *mathVar = dynamic_cast<MathVar *>(var2);
        if (!mathVar)
        {
            panic_throw("Variable %s is not mathimatical", var1);
        }

        return new Integer((*oper)(var1->as_int(), mathVar->as_int()));
    }

    int _math_xor(int a, int b) { return a ^ b; }
    int _math_or(int a, int b) { return a | b; }
    int _math_and(int a, int b) { return a & b; }

    int _math_add(int a, int b) { return a + b; }
    int _math_subtract(int a, int b) { return a - b; }
    int _math_divide(int a, int b) { return a / b; }
    int _math_multiply(int a, int b) { return a * b; }
}