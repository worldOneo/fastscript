#include "PrintFunction.hpp"
#include "../Utility.hpp"
#include <iostream>

namespace fastscript::runtime
{
    Variable *PrintFunction::execute(std::vector<Variable *> args)
    {
        if (args.capacity() != 1)
        {
            std::cout << "Too many arguements: " << args.capacity() << std::endl;
            for (auto parsed_token : args)
            {
                Integer* intVar = dynamic_cast<Integer*>(parsed_token);
                std::cout << intVar->getValue() << std::endl;
            }
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
}
