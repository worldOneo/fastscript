#include "Function.hpp"

namespace fastscript::runtime
{
    class PrintFunction : public Function
    {
    public:
        Variable *execute(std::vector<Variable *> args);
    };
}