#pragma once
#include <string>
#include <vector>
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
        ARRAY,
    };

    class Variable
    {
    private:
        bool free = true;

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
        virtual Variable *modulo(Variable *variable)
        {
            panic_throw("Modulo not implemented for %s", this);
        }
        virtual std::string name()
        {
            return "undefined";
        };
        bool isFree() { return this->free; }
        void setFree(bool val) { this->free = val; }
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

    class Sized
    {
    public:
        virtual int get_size() { return 0; };
    };

    class String : public Variable, public StringAble, public Sized
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
        int get_size();
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
        Variable *add(Variable *);
        Integer *modulo(Variable *);
        Integer *multiply(Variable *);
        Integer *subtract(Variable *);
        Integer *divide(Variable *);
        Integer *lor(Variable *);
        Integer *land(Variable *);
        Integer *lxor(Variable *);
        Integer *lshft(Variable *);
        Integer *rshft(Variable *);
        Boolean *greater(Variable *);
        Boolean *less(Variable *);
        Boolean *equals(Variable *);
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
        Integer *add(Variable *);
        Integer *multiply(Variable *);
        Integer *subtract(Variable *);
        Integer *divide(Variable *);
        Boolean *greater(Variable *);
        Boolean *less(Variable *);
        Boolean *equals(Variable *);
        Integer *modulo(Variable *);
        //Integer *lnot();
        std::string to_string() { return this->value ? "true" : "false"; }
        int as_int() { return this->value; }
        bool getValue() { return this->value; }
        std::string name() { return "Boolean"; };
        Boolean(std::string value);
        Boolean(bool value);
    };

    class Array : public Variable, public StringAble, public Sized //, public Comparator
    {
    private:
        size_t size = 16;
        size_t index = 0;
        Variable **data = new Variable *[16];
        void resize();

    public:
        Variable *add(Variable *var);
        Variable *get(int i);
        Variable *set_index(int i, Variable *var);
        std::string to_string();
        std::string name() { return "Array"; }
        int get_size();
        Array();
    };
}