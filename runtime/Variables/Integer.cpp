#include "Variable.hpp"
#include "../Utility.hpp"

namespace fastscript::runtime
{
    Integer::Integer(Types type, std::string data)
    {
        if (type != INTEGER)
        {
            throw std::runtime_error("Type INTEGER is required for Variable INTEGER");
        }
        this->mType = INTEGER;
        this->data = std::stoi(data);
    }

    Integer::Integer(int i)
    {
        this->mType = INTEGER;
        this->data = i;
    }

    Integer::Integer()
    {
        this->mType = INTEGER;
        this->data = 0;
    }

    Variable *Integer::add(Variable *v)
    {
        Integer *intVar = dynamic_cast<Integer *>(v);
        if (intVar)
            return new Integer(intVar->as_int() + this->as_int());

        StringAble *stringVar = dynamic_cast<StringAble *>(v);
        if (stringVar)
            return new String(STRING, std::to_string(this->data).append(stringVar->to_string()));

        panic_throw("Unable to add integer and %s", v);
    }

    Integer *Integer::modulo(Variable *v)
    {
        return new Integer(utility::_math_operation(this, v, utility::_math_modulo<int>()));
    }

    Integer *Integer::multiply(Variable *v)
    {
        return new Integer(utility::_math_operation(this, v, utility::_math_multiply<int>()));
    }

    Integer *Integer::divide(Variable *v)
    {
        return new Integer(utility::_math_operation(this, v, utility::_math_divide<int>()));
    }

    Integer *Integer::subtract(Variable *v)
    {
        return new Integer(utility::_math_operation(this, v, utility::_math_subtract<int>()));
    }

    Integer *Integer::land(Variable *var)
    {
        return new Integer(utility::_math_operation(this, var, utility::_math_and<int>()));
    }

    Integer *Integer::lxor(Variable *var)
    {
        return new Integer(utility::_math_operation(this, var, utility::_math_xor<int>()));
    }

    Integer *Integer::lor(Variable *var)
    {
        return new Integer(utility::_math_operation(this, var, utility::_math_or<int>()));
    }

    Integer *Integer::rshft(Variable *var)
    {
        return new Integer(utility::_math_operation(this, var, utility::_math_rshft<int>()));
    }

    Integer *Integer::lshft(Variable *var)
    {
        return new Integer(utility::_math_operation(this, var, utility::_math_lshft<int>()));
    }

    Boolean *Integer::less(Variable *v)
    {
        return new Boolean(utility::_math_operation(this, v, utility::_math_lt<int>()));
    }

    Boolean *Integer::equals(Variable *v)
    {
        return new Boolean(utility::_math_operation(this, v, utility::_math_eq<int>()));
    }

    Boolean *Integer::greater(Variable *v)
    {
        return new Boolean(utility::_math_operation(this, v, utility::_math_gt<int>()));
    }

    std::string Integer::to_string()
    {
        return std::to_string(this->data);
    }

    Integer::~Integer()
    {
    }
}