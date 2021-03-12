#include "Variable.hpp"
#include "../Utility.hpp"
#include <cmath>

namespace fastscript::runtime
{
    double doubleResolver(Variable *var)
    {
        Double *doubleVar = dynamic_cast<Double *>(var);
        if (doubleVar)
            return doubleVar->getValue();

        MathVar *mathVar = dynamic_cast<MathVar *>(var);
        if (mathVar)
            return mathVar->as_int();

        panic_throw("Variable %s cant be resolved as DOUBLE", var);
    }

    Double::Double(std::string i)
    {
        this->mType = INTEGER;
        this->data = std::stod(i);
    }

    Double::Double(double i)
    {
        this->mType = INTEGER;
        this->data = i;
    }

    Variable *Double::add(Variable *v)
    {
        Double *doubleVar = dynamic_cast<Double *>(v);
        if (doubleVar)
            return new Double(doubleVar->getValue() + this->getValue());
        
        Integer *intVar = dynamic_cast<Integer *>(v);
        if (intVar)
            return new Double(intVar->as_int() + this->getValue());

        StringAble *stringVar = dynamic_cast<StringAble *>(v);
        if (stringVar)
            return new String(STRING, std::to_string(this->data).append(stringVar->to_string()));

        panic_throw("Unable to add integer and %s", v);
    }

    Double *Double::modulo(Variable *v)
    {
        double (*modulo)(double, double) = [](double a, double b) { return std::fmod(a, b); };
        return new Double(utility::_math_operation(this, v, modulo, doubleResolver));
    }

    Double *Double::multiply(Variable *v)
    {
        double (*modulo)(double, double) = [](double a, double b) { return std::fmod(a, b); };
        return new Double(utility::_math_operation(this, v, utility::_math_multiply<double>(), doubleResolver));
    }

    Double *Double::divide(Variable *v)
    {
        return new Double(utility::_math_operation(this, v, utility::_math_divide<double>(), doubleResolver));
    }

    Double *Double::subtract(Variable *v)
    {
        return new Double(utility::_math_operation(this, v, utility::_math_subtract<double>(), doubleResolver));
    }

    Boolean *Double::less(Variable *v)
    {
        return new Boolean(utility::_math_operation(this, v, utility::_math_lt<double>(), doubleResolver));
    }

    Boolean *Double::equals(Variable *v)
    {
        return new Boolean(utility::_math_operation(this, v, utility::_math_eq<double>(), doubleResolver));
    }

    Boolean *Double::greater(Variable *v)
    {
        return new Boolean(utility::_math_operation(this, v, utility::_math_gt<double>(), doubleResolver));
    }

    std::string Double::to_string()
    {
        return std::to_string(this->data);
    }

    Double::~Double()
    {
    }
}