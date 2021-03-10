#pragma once
#include <vector>
#include <map>
#include "Tokens.hpp"
#include "runtime/Variables/Variable.hpp"
#include "runtime/Functions/Function.hpp"

namespace fastscript::parser
{
    enum Operations
    {
        ADD,
        SUBTRACT,
        MULTIPLY,
        DIVIDE
    };

    class Parser
    {
    private:
        std::map<std::string, runtime::Variable *> mVariableMap;
        std::map<std::string, runtime::Function *> mFunctionMap;
        void asign(token::Token *currToken, token::Token *tokens[], int *idx);
        runtime::Variable *funcionCall(token::Token *tInvoke, token::Token *tokens[], int *idx);
        runtime::Variable *nextVariable(token::Token *tInvoke, token::Token *tokens[], int *idx);

    public:
        void parse(std::vector<fastscript::token::Token *> program);
    };
}