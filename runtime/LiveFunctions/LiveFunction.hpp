#include <stddef.h>
#include "../../Tokenizer.hpp"

namespace fastscript::runtime
{
    class LiveFunction
    {
    private:
        int mEnd;
        int mStart;
        std::vector<token::Token *> mParameters;

    public:
        int getStart();
        int getEnd();
        std::vector<token::Token *> getParameters();
        LiveFunction(int, int, std::vector<token::Token *> params);
    };
}