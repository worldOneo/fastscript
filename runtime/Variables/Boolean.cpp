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
        return new Integer(utility::_math_operation(this, var, utility::_math_rshft<int>()));
    }

    Integer *Boolean::lshft(Variable *var)
    {
        return new Integer(utility::_math_operation(this, var, utility::_math_lshft<int>()));
    }

    Integer *Boolean::land(Variable *var)
    {
        return new Integer(utility::_math_operation(this, var, utility::_math_and<int>()));
    }

    Integer *Boolean::lxor(Variable *var)
    {
        return new Integer(utility::_math_operation(this, var, utility::_math_xor<int>()));
    }

    Integer *Boolean::lor(Variable *var)
    {
        return new Integer(utility::_math_operation(this, var, utility::_math_or<int>()));
    }

    Integer *Boolean::modulo(Variable *v)
    {
        return new Integer(utility::_math_operation(this, v, utility::_math_modulo<int>()));
    }

    Integer *Boolean::add(Variable *v)
    {
        return new Integer(utility::_math_operation(this, v, utility::_math_add<int>()));
    }

    Integer *Boolean::multiply(Variable *v)
    {
        return new Integer(utility::_math_operation(this, v, utility::_math_multiply<int>()));
    }

    Integer *Boolean::divide(Variable *v)
    {
        return new Integer(utility::_math_operation(this, v, utility::_math_divide<int>()));
    }

    Integer *Boolean::subtract(Variable *v)
    {
        return new Integer(utility::_math_operation(this, v, utility::_math_subtract<int>()));
    }

    Boolean *Boolean::less(Variable *v)
    {
        return new Boolean(utility::_math_operation(this, v, utility::_math_gt<int>()));
    }

    Boolean *Boolean::equals(Variable *v)
    {
        return new Boolean(utility::_math_operation(this, v, utility::_math_eq<int>()));
    }

    Boolean *Boolean::greater(Variable *v)
    {
        return new Boolean(utility::_math_operation(this, v, utility::_math_gt<int>()));
    }
}