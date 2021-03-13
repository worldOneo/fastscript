#include "LiveFunction.hpp"

namespace fastscript::runtime
{
    int LiveFunction::getEnd() { return this->mEnd; }
    int LiveFunction::getStart() { return this->mStart; }
    std::vector<token::Token *> LiveFunction::getParameters() { return this->mParameters; }
    LiveFunction::LiveFunction(int start, int end, std::vector<token::Token *> params)
    {
        this->mStart = start;
        this->mEnd = end;
        this->mParameters = params;
    }

}
