#pragma once
#include <vector>
#include <map>
#include "Tokenizer.hpp"
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
        std::map<std::string, std::string> mOperatorMap;
        std::map<std::string, std::string> mComparatorMap;
        std::map<std::string, std::string> mCondBitwiseMap;


        std::vector<std::pair<int, int>> mStack;
        size_t mBraceCount = 0;

        void asign(token::Token *currToken, token::Token *tokens[], int *idx);
        runtime::Variable *funcionCall(token::Token *tInvoke, token::Token *tokens[], int *idx);
        runtime::Variable *nextVariable(token::Token *tokens[], int *idx);
        runtime::Variable *nextVariable(token::Token *tokens[], int *idx, bool allowComparison);
        runtime::Variable *evaluateMapOperation(std::map<std::string, std::string> operationMap,
                                                                int *idx, token::Token *potentialOperator,
                                                                token::Token *tokens[], runtime::Variable *var,
                                                                bool allowComparison);
        bool exceptOperator(std::string excepted, token::Token *tokens[], int *idx);
        void skipScope(token::Token *tokens[], int *idx);

    public:
        Parser();
        void parse(std::vector<fastscript::token::Token *> program);
    };
}