#include "MathFunctions.hpp"
#include "../Utility.hpp"

namespace fastscript::runtime
{
    MathVar *ensure_mathvar(Variable *v)
    {
        MathVar *mathVar = dynamic_cast<MathVar *>(v);
        if (!mathVar)
        {
            panic_throw("Variable %s isn't mathematical", v);
        }
        return mathVar;
    }

    Variable *Add::execute(std::vector<Variable *> args)
    {
        return args.at(0)->add(args.at(1));
    }

    Variable *Subtract::execute(std::vector<Variable *> args)
    {
        return args.at(0)->subtract(args.at(1));
    }

    Variable *Multiply::execute(std::vector<Variable *> args)
    {
        return args.at(0)->multiply(args.at(1));
    }

    Variable *Divide::execute(std::vector<Variable *> args)
    {
        return args.at(0)->divide(args.at(1));
    }

    Variable *LogicOR::execute(std::vector<Variable *> args)
    {
        MathVar *mathVar = ensure_mathvar(args.at(0));
        return mathVar->lor(args.at(1));
    }

    Variable *LogicXOR::execute(std::vector<Variable *> args)
    {
        MathVar *mathVar = ensure_mathvar(args.at(0));
        return mathVar->lxor(args.at(1));
    }

    Variable *LogicAND::execute(std::vector<Variable *> args)
    {
        MathVar *mathVar = ensure_mathvar(args.at(0));
        return mathVar->land(args.at(1));
    }

    Variable *LogicRSHFT::execute(std::vector<Variable *> args)
    {
        MathVar *mathVar = ensure_mathvar(args.at(0));
        return mathVar->rshft(args.at(1));
    }

    Variable *LogicLSHFT::execute(std::vector<Variable *> args)
    {
        MathVar *mathVar = ensure_mathvar(args.at(0));
        return mathVar->lshft(args.at(1));
    }

    Variable *AsBoolean::execute(std::vector<Variable *> args)
    {
        MathVar *mathVar = ensure_mathvar(args.at(0));
        return new Boolean(mathVar->as_int());
    }

    Variable *AsInteger::execute(std::vector<Variable *> args)
    {
        MathVar *mathVar = dynamic_cast<MathVar *>(args.at(0));
        if (mathVar)
        {
            return new Integer(mathVar->as_int());
        }
        StringAble *stringVar = dynamic_cast<StringAble *>(args.at(0));
        if (stringVar)
        {
            return new Integer(std::stoi(stringVar->to_string()));
        }
        panic_throw("Varible %s cant be converted to Integer", args.at(0));
    }

    Variable *Modulo::execute(std::vector<Variable *> args)
    {
        MathVar *mathVar = ensure_mathvar(args.at(0));
        return mathVar->modulo(args.at(1));
    }

    Variable *CondAND::execute(std::vector<Variable *> args)
    {
        MathVar *mathVar1 = ensure_mathvar(args.at(0));
        MathVar *mathVar2 = ensure_mathvar(args.at(1));
        return new Boolean(mathVar1->as_int() && mathVar2->as_int());
    }

    Variable *CondOR::execute(std::vector<Variable *> args)
    {
        MathVar *mathVar1 = ensure_mathvar(args.at(0));
        MathVar *mathVar2 = ensure_mathvar(args.at(1));
        return new Boolean(mathVar1->as_int() || mathVar2->as_int());
    }
}