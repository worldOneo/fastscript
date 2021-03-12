#include "Variable.hpp"
#include "../Utility.hpp"

#define _math_shortdefinitionz(x, y)       \
    template <typename V, typename Z>      \
    utility::_result<V, Z> _math_##x()     \
    {                                      \
        return [](V a, V b) { return y; }; \
    }

namespace fastscript::runtime
{

    _math_shortdefinitionz(str_eq, a == b);
    _math_shortdefinitionz(str_gt, a > b);
    _math_shortdefinitionz(str_lt, a < b);

    std::string stringResolver(Variable *var)
    {
        StringAble *stringAble = dynamic_cast<StringAble *>(var);
        if (stringAble)
        {
            return stringAble->to_string();
        }

        panic_throw("Cant convert %s to STRING", var);
    }

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

    Boolean *String::equals(Variable *var)
    {
        return new Boolean(utility::_math_operationz(this, var, _math_str_eq<std::string, bool>(), stringResolver));
    }

    Boolean *String::greater(Variable *var)
    {
        return new Boolean(utility::_math_operationz(this, var, _math_str_gt<std::string, bool>(), stringResolver));
    }

    Boolean *String::less(Variable *var)
    {
        return new Boolean(utility::_math_operationz(this, var, _math_str_lt<std::string, bool>(), stringResolver));
    }

    int String::get_size()
    {
        return this->data.size();
    }

    std::string String::to_string()
    {
        return this->data;
    }
}
