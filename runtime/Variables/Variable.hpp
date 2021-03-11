#pragma once
#include <string>
#include "stdexcept"

#define panic_throw(msg, v)                    \
    char err[50];                              \
    std::sprintf(err, msg, v->name().c_str()); \
    throw std::runtime_error(std::string(err));

namespace fastscript::runtime
{

    enum Types
    {
        STRING,
        INTEGER
    };

    class Variable
    {
    public:
        virtual Variable *add(Variable *variable)
        {
            panic_throw("Add not implemented for %s", this);
        };
        virtual Variable *subtract(Variable *variable)
        {
            panic_throw("Subtract not implemented for %s", this);
        };
        virtual Variable *multiply(Variable *variable)
        {
            panic_throw("Multiply not implemented for %s", this);
        };
        virtual Variable *divide(Variable *variable)
        {
            panic_throw("Divide not implemented for %s", this);
        };
        virtual std::string name()
        {
            return "undefined";
        };
        Variable(Types type, std::string data);
        Variable();
        virtual ~Variable(){};
        Types mType;
    };

    class StringAble
    {
    public:
        virtual std::string to_string() { return "to_string not implemented";};
    };

    class Integer : public Variable, public StringAble
    {
    protected:
        int data;

    public:
        std::string name() { return "Integer"; }
        std::string to_string();
        int getValue() { return this->data; };
        Variable *add(Variable *variable);
        Integer *multiply(Variable *variable);
        Integer *subtract(Variable *variable);
        Integer *divide(Variable *variable);
        Integer(Types type, std::string data);
        Integer(int i);
        Integer();
        ~Integer();
    };

    class String : public Variable, public StringAble
    {
    protected:
        std::string data;

    public:
        String *add(Variable *variable);
        //String *multiply(Variable *variable);
        //String *subtract(Variable *variable);
        //String *divide(Variable *variable);
        std::string name() { return "string"; }
        String(Types type, std::string data) { this->data = data; };
        std::string to_string();
    };
}