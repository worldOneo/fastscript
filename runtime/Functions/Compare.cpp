#include "Compare.hpp"

namespace fastscript::runtime
{
    Comparator *ensure_comparator(Variable *v)
    {
        Comparator *compVar = dynamic_cast<Comparator *>(v);
        if (!compVar)
        {
            panic_throw("Variable %s isn't mathematical", v);
        }
        return compVar;
    }

    Variable *LogicEQ::execute(std::vector<Variable *> args)
    {
        Comparator *compVar = ensure_comparator(args.at(0));
        return compVar->equals(args.at(1));
    }

    Variable *LogicGT::execute(std::vector<Variable *> args)
    {
        Comparator *compVar = ensure_comparator(args.at(0));
        return compVar->greater(args.at(1));
    }

    Variable *LogicLT::execute(std::vector<Variable *> args)
    {
        Comparator *compVar = ensure_comparator(args.at(0));
        return compVar->less(args.at(1));
    }

    Variable *LogicLTEQ::execute(std::vector<Variable *> args)
    {
        Comparator *compVar = ensure_comparator(args.at(0));
        Boolean *equals = compVar->equals(args.at(1));
        if (equals->getValue())
            return equals;
        return new Boolean(equals->lor(equals->less(args.at(0))));
    }

    Variable *LogicGTEQ::execute(std::vector<Variable *> args)
    {
        Comparator *compVar = ensure_comparator(args.at(0));
        Boolean *equals = compVar->greater(args.at(1));
        if (equals->getValue())
            return equals;
        return new Boolean(equals->lor(equals->equals(args.at(0))));
    }
}