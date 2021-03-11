#include "Variable.hpp"

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
        {
            return new Integer(intVar->getValue() + this->getValue());
        }
        StringAble *stringVar = dynamic_cast<StringAble *>(v);
        if (stringVar)
        {
            return new String(STRING, std::to_string(this->data).append(stringVar->to_string()));
        }
        panic_throw("Unable to add integer and %s", v);
    }

    Integer *Integer::multiply(Variable *v)
    {
        Integer *intVar = dynamic_cast<Integer *>(v);
        if (intVar)
        {
            return new Integer(this->getValue() * intVar->getValue());
        }
        panic_throw("Unable to multiply integer and %s", v);
    }

    Integer *Integer::divide(Variable *v)
    {
        Integer *intVar = dynamic_cast<Integer *>(v);
        if (intVar)
        {
            return new Integer(this->getValue() / intVar->getValue());
        }
        panic_throw("Unable to divide integer and %s", v);
    }

    Integer *Integer::subtract(Variable *v)
    {
        Integer *intVar = dynamic_cast<Integer *>(v);
        if (intVar)
        {
            return new Integer(this->getValue() - intVar->getValue());
        }
        panic_throw("Unable to subtract integer and %s", v);
    }

    std::string Integer::to_string()
    {
        return std::to_string(this->data);
    }

    Integer::~Integer()
    {
    }
}