#include "MathFunctions.hpp"
#include "../Utility.hpp"

namespace fastscript::runtime
{

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
        MathVar *mathVar = dynamic_cast<MathVar *>(args.at(0));
        if (!mathVar)
        {
            panic_throw("Variable %s isn't mathematical", args.at(0));
        }
        return utility::_math_operation(mathVar, args.at(1), utility::_math_or);
    }

    Variable *LogicXOR::execute(std::vector<Variable *> args)
    {
        MathVar *mathVar = dynamic_cast<MathVar *>(args.at(0));
        if (!mathVar)
        {
            panic_throw("Variable %s isn't mathematical", args.at(0));
        }
        return utility::_math_operation(mathVar, args.at(1), utility::_math_xor);
    }

    Variable *LogicAND::execute(std::vector<Variable *> args)
    {
        MathVar *mathVar = dynamic_cast<MathVar *>(args.at(0));
        if (!mathVar)
        {
            panic_throw("Variable %s isn't mathematical", args.at(0));
        }
        return utility::_math_operation(mathVar, args.at(1), utility::_math_and);
    }

    Variable *AsBoolean::execute(std::vector<Variable *> args)
    {
        MathVar *mathVar = dynamic_cast<MathVar *>(args.at(0));
        if (!mathVar)
        {
            panic_throw("Variable %s isn't mathematical", args.at(0));
        }
        return new Boolean(mathVar->as_int());
    }
}