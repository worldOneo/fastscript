#include "Variable.hpp"
#include "../Utility.hpp"

namespace fastscript::runtime
{
    Boolean::Boolean(std::string value)
    {
        this->value = value == "true" ? true : false;
        this->mType = BOOLEAN;
    }

    Boolean::Boolean(bool value)
    {
        this->value = value;
        this->mType = BOOLEAN;
    }

    Integer *Boolean::rshft(Variable *var)
    {
        return new Integer(utility::_math_operation(this, var, utility::_math_rshft));
    }

    Integer *Boolean::lshft(Variable *var)
    {
        return new Integer(utility::_math_operation(this, var, utility::_math_lshft));
    }

    Integer *Boolean::land(Variable *var)
    {
        return new Integer(utility::_math_operation(this, var, utility::_math_and));
    }

    Integer *Boolean::lxor(Variable *var)
    {
        return new Integer(utility::_math_operation(this, var, utility::_math_xor));
    }

    Integer *Boolean::lor(Variable *var)
    {
        return new Integer(utility::_math_operation(this, var, utility::_math_or));
    }

    Integer *Boolean::add(Variable *v)
    {
        return new Integer(utility::_math_operation(this, v, utility::_math_add));
    }

    Integer *Boolean::multiply(Variable *v)
    {
        return new Integer(utility::_math_operation(this, v, utility::_math_multiply));
    }

    Integer *Boolean::divide(Variable *v)
    {
        return new Integer(utility::_math_operation(this, v, utility::_math_divide));
    }

    Integer *Boolean::subtract(Variable *v)
    {
        return new Integer(utility::_math_operation(this, v, utility::_math_subtract));
    }

    Boolean *Boolean::less(Variable *v)
    {
        return new Boolean(utility::_math_operation(this, v, utility::_math_gt));
    }

    Boolean *Boolean::equals(Variable *v)
    {
        return new Boolean(utility::_math_operation(this, v, utility::_math_eq));
    }

    Boolean *Boolean::greater(Variable *v)
    {
        return new Boolean(utility::_math_operation(this, v, utility::_math_gt));
    }
}