#include "Variable.hpp"
#include "stdexcept"

using namespace fastscript::runtime;

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
        int i = intVar->getValue();
        int m = this->getValue();
        return new Integer(i + m);
    }
    String *stringVar = dynamic_cast<String *>(v);
    if (stringVar)
    {
        return new String(STRING, std::to_string(this->data).append(stringVar->getValue()));
    }
    char err[50];
    std::sprintf(err, "Unable to add integer and %s", v->name().c_str());
    throw std::runtime_error(std::string(err));
}

Integer *Integer::multiply(Variable *v)
{
    Integer *intVar = dynamic_cast<Integer *>(v);
    if (intVar)
    {
        int i = intVar->getValue();
        int m = this->getValue();
        return new Integer(i * m);
    }
    char err[50];
    std::sprintf(err, "Unable to multiply integer and %s", v->name().c_str());
    throw std::runtime_error(std::string(err));
}

Integer *Integer::divide(Variable *v)
{
    Integer *intVar = dynamic_cast<Integer *>(v);
    if (intVar)
    {
        int i = intVar->getValue();
        int m = this->getValue();
        return new Integer(m / i);
    }
    char err[50];
    std::sprintf(err, "Unable to divide integer and %s", v->name().c_str());
    throw std::runtime_error(std::string(err));
}

Integer *Integer::subtract(Variable *v)
{
    Integer *intVar = dynamic_cast<Integer *>(v);
    if (intVar)
    {
        int i = intVar->getValue();
        int m = this->getValue();
        return new Integer(m - i);
    }
    char err[50];
    std::sprintf(err, "Unable to subtract integer and %s", v->name().c_str());
    throw std::runtime_error(std::string(err));
}

Integer::~Integer()
{
}