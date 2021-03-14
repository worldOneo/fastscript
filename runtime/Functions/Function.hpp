#pragma once
#include "../Variables/Variable.hpp"
#include <vector>

#define function_with_name(r)                             \
    class r : public Function                             \
    {                                                     \
    public:                                               \
        Variable *execute(std::vector<Variable *> &args); \
    };

namespace fastscript::runtime
{
    class Function
    {
    public:
        virtual Variable *execute(std::vector<Variable *> &args)
        {
            return new Variable();
        };
    };
}