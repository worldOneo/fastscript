#include "Variable.hpp"
#include "stdexcept"

namespace fastscript::runtime
{
    String *String::add(Variable *var)
    {
        String *strVar = dynamic_cast<String *>(var);
        std::string newString = this->getValue();
        if (strVar)
        {
            std::string append = strVar->getValue();
            return new String(STRING, newString.append(append));
        }

        Integer *intVar = dynamic_cast<Integer *>(var);
        if (intVar)
        {
            return new String(STRING, newString + std::to_string(intVar->getValue()));
        }
        char err[50];
        std::sprintf(err, "Unable to add string and %s", var->name().c_str());
        throw std::runtime_error(std::string(err));
    }

    std::string String::getValue()
    {
        return this->data;
    }
}
