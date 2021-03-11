#include "PrintFunction.hpp"
#include "../Utility.hpp"
#include <iostream>
#include <sstream>

namespace fastscript::runtime
{
    Variable *PrintFunction::execute(std::vector<Variable *> args)
    {
        if (args.capacity() == 0)
        {
            std::cout << std::endl;
            return nullptr;
        }

        if (args.capacity() > 1)
        {
            std::cout << "Too many arguements: " << args.capacity() << std::endl;
            return nullptr;
        }

        StringAble *stringVar = dynamic_cast<StringAble *>(args[0]);
        if (stringVar)
        {
            std::cout << stringVar->to_string() << std::endl;
            return nullptr;
        }
        else
        {
            std::cout << args[0] << std::endl;
        }
        return nullptr;
    }

    Variable *PrintFormatedFunction::execute(std::vector<Variable *> args)
    {
        if (args.capacity() < 1)
        {
            std::cout << "Not enough args: " << args.capacity() << std::endl;
            return nullptr;
        }
        String *stringVar = dynamic_cast<String *>(args[0]);
        if (stringVar)
        {
            std::string value = stringVar->to_string();
            args.erase(args.begin());
            for (int i = 0; i < args.capacity() - 1; i++)
            {
                StringAble *stringVar = dynamic_cast<StringAble *>(args[i]);
                std::string replace = "{" + std::to_string(i) + "}";
                size_t start_pos = value.find(replace);
                if (start_pos == std::string::npos)
                    continue;
                if (stringVar)
                {
                    value.replace(start_pos, replace.length(), stringVar->to_string());
                }
                else
                {
                    std::ostringstream addr;
                    addr << args[i];
                    value.replace(start_pos, replace.length(), addr.str());
                }
            }
            std::cout << value << std::endl;
        }
        return nullptr;
    }
}
