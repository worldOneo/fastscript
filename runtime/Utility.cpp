#include "Utility.hpp"
#include "iostream"

namespace fastscript::runtime::utility
{

    int intResolver(Variable *Variable)
    {
        MathVar *mathVar = dynamic_cast<MathVar *>(Variable);
        if (!mathVar)
        {
            panic_throw("Variable %s is not mathimatical", mathVar);
        }
        return mathVar->as_int();
    }
}