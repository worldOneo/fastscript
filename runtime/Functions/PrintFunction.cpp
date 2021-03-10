#include "PrintFunction.hpp"
#include "../Utility.hpp"
#include <iostream>

using namespace fastscript::runtime;

Variable *fastscript::runtime::PrintFunction::execute(std::vector<Variable *> args)
{
    if (args.capacity() != 1)
    {
        std::cout << "-" << std::endl;
        return nullptr;
    }
    String *stringVar = dynamic_cast<String *>(args[0]);
    if (stringVar)
    {
        std::cout << stringVar->getValue() << std::endl;
        return nullptr;
    }

    Integer *intVar = dynamic_cast<Integer *>(args[0]);
    if (intVar)
    {
        std::cout << intVar->getValue() << std::endl;
        return nullptr;
    }
}
