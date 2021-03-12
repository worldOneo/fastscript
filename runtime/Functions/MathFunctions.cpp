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

    Variable *Modulo::execute(std::vector<Variable *> args)
    {
        MathVar *mathVar = ensure_mathvar(args.at(0));
        return mathVar->modulo(args.at(1));
    }
}