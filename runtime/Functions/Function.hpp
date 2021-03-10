#pragma once
#include "../Variables/Variable.hpp"
#include <vector>

namespace fastscript::runtime
{
    class Function
    {
    public:
        virtual Variable *execute(std::vector<Variable *> args){
            return new Variable();
        };
    };
}