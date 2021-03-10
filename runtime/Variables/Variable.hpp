#pragma once
#include <string>

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
            return variable;
        };
        virtual Variable *subtract(Variable *variable)
        {
            return variable;
        };
        virtual Variable *multiply(Variable *variable)
        {
            return variable;
        };
        virtual Variable *divide(Variable *variable)
        {
            return variable;
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

    class Integer : public Variable
    {
    protected:
        double data;

    public:
        std::string name() { return "Integer"; }
        int getValue() { return this->data; };
        Integer *add(Variable *variable);
        Integer *multiply(Variable *variable);
        Integer *subtract(Variable *variable);
        Integer *divide(Variable *variable);
        Integer(Types type, std::string data);
        Integer(int i);
        Integer();
        ~Integer();
    };

    class String : public Variable
    {
    protected:
        std::string data;

    public:
        //String *add(Variable *variable);
        //String *multiply(Variable *variable);
        //String *subtract(Variable *variable);
        //String *divide(Variable *variable);
        std::string name() { return "string"; }
        String(Types type, std::string data) { this->data = data; };
        std::string getValue() { return this->data; };
    };
}