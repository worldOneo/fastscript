#include "Variable.hpp"

namespace fastscript::runtime
{
    String *String::add(Variable *var)
    {
        StringAble *strVar = dynamic_cast<StringAble *>(var);
        std::string newString = this->to_string();
        if (strVar)
        {
            std::string append = strVar->to_string();
            return new String(STRING, newString.append(append));
        }
        panic_throw("Unable to add string and %s", var);
    }

    std::string String::to_string()
    {
        return this->data;
    }
}
