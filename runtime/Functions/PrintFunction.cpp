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
                Integer *intVar = dynamic_cast<Integer *>(parsed_token);
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
        }
        return nullptr;
    }

    Variable *PrintFormatedFunction::execute(std::vector<Variable *> args)
    {
        if (args.capacity() < 1)
        {
            std::cout << "Not enough args: " << args.capacity() << std::endl;
            for (auto parsed_token : args)
            {
                Integer *intVar = dynamic_cast<Integer *>(parsed_token);
                std::cout << intVar->getValue() << std::endl;
            }
            return nullptr;
        }
        String *stringVar = dynamic_cast<String *>(args[0]);
        if (stringVar)
        {
            std::string value = stringVar->getValue();
            args.erase(args.begin());
            for (int i = 0; i < args.capacity(); i++)
            {
                Integer *intVar = dynamic_cast<Integer *>(args[i]);
                String *stringVar = dynamic_cast<String *>(args[i]);
                std::string replace = "{" + std::to_string(i) + "}";
                size_t start_pos = value.find(replace);
                if (start_pos == std::string::npos)
                    continue;
                if (intVar)
                {
                    value = value.replace(start_pos, replace.length(), std::to_string(intVar->getValue()));
                }
                else if (stringVar)
                {
                    value = value.replace(start_pos, replace.length(), stringVar->getValue());
                }
            }
            std::cout << value << std::endl;
        }
        return nullptr;
    }
}
