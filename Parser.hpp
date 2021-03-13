#pragma once
#include <vector>
#include <map>
#include "Tokenizer.hpp"
#include "runtime/Variables/Variable.hpp"
#include "runtime/Functions/Function.hpp"
#include "runtime/LiveFunctions/LiveFunction.hpp"

namespace fastscript::parser
{
    enum Operations
    {
        ADD,
        SUBTRACT,
        MULTIPLY,
        DIVIDE
    };

    void printToken(token::Token *);
    void panic(std::string, token::Token *);

    class Parser
    {
    private:
        std::map<std::string, runtime::Variable *> *mVariableMap = new std::map<std::string, runtime::Variable *>();
        std::map<std::string, runtime::Function *> mFunctionMap;
        std::map<std::string, runtime::LiveFunction *> mLiveFunctionMap;

        std::vector<std::map<std::string, runtime::Variable *> *> mScopedVariables;

        std::map<std::string, std::string> mOperatorMap;
        std::map<std::string, std::string> mComparatorMap;
        std::map<std::string, std::string> mCondBitwiseMap;

        std::vector<std::pair<int, int>> mStack;
        size_t mBraceCount = 0;

        void asign(token::Token *currToken, token::Token *tokens[], int *idx);
        runtime::Variable *functionCall(token::Token *tInvoke, token::Token *tokens[], int *idx);
        runtime::LiveFunction *functionDefinition(token::Token *tokens[], int *idx);
        runtime::Variable *nextVariable(token::Token *tokens[], int *idx);
        runtime::Variable *nextVariable(token::Token *tokens[], int *idx, bool allowComparison);
        runtime::Variable *evaluateMapOperation(std::map<std::string, std::string> operationMap,
                                                int *idx, token::Token *potentialOperator,
                                                token::Token *tokens[], runtime::Variable *var,
                                                bool allowComparison);
        std::map<std::string, runtime::Variable *> *getVarScope(std::string);
        bool exceptOperator(std::string excepted, token::Token *tokens[], int *idx);
        void skipScope(token::Token *tokens[], int *idx);

    public:
        Parser();
        void parse(std::vector<fastscript::token::Token *> program);
    };
}