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
        INTEGER,
        BOOLEAN,
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

    class MathVar : public Variable
    {
    public:
        virtual Variable *lor(Variable *variable)
        {
            panic_throw("OR not implemented for %s", this);
        };
        virtual Variable *land(Variable *variable)
        {
            panic_throw("AND not implemented for %s", this);
        };
        virtual Variable *lxor(Variable *variable)
        {
            panic_throw("XOR not implemented for %s", this);
        };
        virtual Variable *rshft(Variable *variable)
        {
            panic_throw("Right-shift not implemented for %s", this);
        };
        virtual Variable *lshft(Variable *variable)
        {
            panic_throw("Right-shift not implemented for %s", this);
        };
        virtual int as_int()
        {
            return 0;
        };
    };

    class StringAble
    {
    public:
        virtual std::string to_string() { return "to_string not implemented"; };
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
        std::string name() { return "String"; }
        String(Types type, std::string data) { this->data = data; };
        std::string to_string();
    };

    class Boolean;

    class Comparator
    {
    public:
        virtual Boolean *greater(Variable *variable) { return nullptr; };
        virtual Boolean *less(Variable *variable) { return nullptr; };
        virtual Boolean *equals(Variable *variable) { return nullptr; };
    };

    class Integer : public MathVar, public StringAble, public Comparator
    {
    protected:
        int data;

    public:
        std::string name() { return "Integer"; }
        std::string to_string();
        int as_int() { return this->data; }
        Variable *add(Variable *variable);
        Integer *multiply(Variable *variable);
        Integer *subtract(Variable *variable);
        Integer *divide(Variable *variable);
        Integer *lor(Variable *);
        Integer *land(Variable *);
        Integer *lxor(Variable *);
        Integer *lshft(Variable *);
        Integer *rshft(Variable *);
        Boolean *greater(Variable *variable);
        Boolean *less(Variable *variable);
        Boolean *equals(Variable *variable);
        Integer(Types type, std::string data);
        Integer(int i);
        Integer();
        ~Integer();
    };

    class Boolean : public MathVar, public StringAble, public Comparator
    {
    protected:
        bool value;

    public:
        Integer *lshft(Variable *);
        Integer *rshft(Variable *);
        Integer *lor(Variable *);
        Integer *land(Variable *);
        Integer *lxor(Variable *);
        Integer *add(Variable *variable);
        Integer *multiply(Variable *variable);
        Integer *subtract(Variable *variable);
        Integer *divide(Variable *variable);
        Boolean *greater(Variable *variable);
        Boolean *less(Variable *variable);
        Boolean *equals(Variable *variable);
        //Integer *lnot();
        std::string to_string() { return this->value ? "true" : "false"; }
        int as_int() { return this->value; }
        bool getValue() { return this->value; }
        std::string name() { return "Boolean"; };
        Boolean(std::string value);
        Boolean(bool value);
    };
}