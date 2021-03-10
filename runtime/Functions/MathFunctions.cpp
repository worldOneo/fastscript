#include "MathFunctions.hpp"

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

}