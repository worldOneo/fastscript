#include <map>
#include <iostream>
#include "Parser.hpp"
#include "runtime/Variables/Variable.hpp"
#include "runtime/Functions/PrintFunction.hpp"
#include "runtime/Functions/MathFunctions.hpp"
#include "runtime/Functions/Compare.hpp"

using namespace fastscript;

void printToken(token::Token *tval)
{
    std::cout << token::T_CANONICAL[tval->mType]
              << " " << tval->mContent << " line: "
              << tval->mLine << std::endl;
}

void panic(std::string str, token::Token *tval)
{
    printToken(tval);
    throw std::runtime_error(str);
}

parser::Parser::Parser()
{
    //util
    this->mFunctionMap["print"] = new runtime::PrintFunction();
    this->mFunctionMap["printf"] = new runtime::PrintFormatedFunction();
    this->mFunctionMap["boolean"] = new runtime::AsBoolean();

    //Math
    this->mFunctionMap["add"] = new runtime::Add();
    this->mFunctionMap["subtract"] = new runtime::Subtract();
    this->mFunctionMap["multiply"] = new runtime::Multiply();
    this->mFunctionMap["divide"] = new runtime::Divide();
    this->mFunctionMap["modulo"] = new runtime::Modulo();

    //Bit-Math
    this->mFunctionMap["xor"] = new runtime::LogicXOR();
    this->mFunctionMap["and"] = new runtime::LogicAND();
    this->mFunctionMap["or"] = new runtime::LogicOR();
    this->mFunctionMap["rshft"] = new runtime::LogicRSHFT();
    this->mFunctionMap["lshft"] = new runtime::LogicLSHFT();

    //Comparison
    this->mFunctionMap["equal"] = new runtime::LogicEQ();
    this->mFunctionMap["gt"] = new runtime::LogicGT();
    this->mFunctionMap["lt"] = new runtime::LogicLT();
    this->mFunctionMap["gteq"] = new runtime::LogicGTEQ();
    this->mFunctionMap["lteq"] = new runtime::LogicLTEQ();
    this->mFunctionMap["cand"] = new runtime::CondAND();
    this->mFunctionMap["cor"] = new runtime::CondOR();

    //Symbol-mapping
    this->mOperatorMap["+"] = "add";
    this->mOperatorMap["-"] = "subtract";
    this->mOperatorMap["*"] = "multiply";
    this->mOperatorMap["/"] = "divide";
    this->mOperatorMap["%"] = "modulo";
    this->mOperatorMap["^"] = "xor";
    this->mOperatorMap["|"] = "or";
    this->mOperatorMap["&"] = "and";
    this->mOperatorMap["<<"] = "lshft";
    this->mOperatorMap[">>"] = "rshft";
    this->mOperatorMap[">>"] = "rshft";

    this->mComparatorMap["=="] = "equal";
    this->mComparatorMap[">"] = "gt";
    this->mComparatorMap["<"] = "lt";
    this->mComparatorMap["<="] = "lteq";
    this->mComparatorMap[">="] = "gteq";

    this->mCondBitwiseMap["&&"] = "cand";
    this->mCondBitwiseMap["||"] = "cor";
}

void parser::Parser::parse(std::vector<token::Token *> program)
{
    token::Token *currToken;
    token::Token *toper;
    token::Token *tokens[program.capacity()];
    std::copy(program.begin(), program.end(), tokens);
    int index = 0;
    while (index < program.capacity())
    {
        currToken = tokens[index];
        switch (currToken->mType)
        {
        case token::IDENTIFIER:
            toper = tokens[++index];
            if (toper->mType == token::OPERATOR)
            {
                if (toper->mContent == "=")
                {
                    this->asign(currToken, tokens, &index);
                }
                else if (toper->mContent == "(")
                {
                    this->funcionCall(currToken, tokens, &index);
                }
                else if (toper->mContent == "[")
                {
                    if (this->mVariableMap.find(currToken->mContent) == this->mVariableMap.end())
                        panic("Variable not defined", currToken);

                    runtime::Array *arrayVar = dynamic_cast<runtime::Array *>(
                        this->mVariableMap[currToken->mContent]);

                    if (!arrayVar)
                        panic("Invalid access", currToken);

                    runtime::Variable *access = this->nextVariable(tokens, &index);

                    runtime::MathVar *mathVar = dynamic_cast<runtime::MathVar *>(access);
                    if (!mathVar)
                        panic("Array access without mathematical var!", toper);

                    int accessIndex = mathVar->as_int();

                    if (!exceptOperator("]", tokens, &index))
                        panic("] ecepted, unclosed array access", currToken);

                    if (!exceptOperator("=", tokens, &index))
                        panic("= excepted, unfinished array definition.", currToken);

                    runtime::Variable *value = this->nextVariable(tokens, &index);
                    arrayVar->set_index(accessIndex, value);
                }
                break;
            }
            break;
        case token::OPERATOR:
            if (currToken->mContent == "}" && !this->mStack.empty())
            {
                std::pair<int, int> poped = this->mStack.at(this->mStack.size() - 1);
                if (poped.first == mBraceCount)
                {
                    index = poped.second;
                    this->mStack.pop_back();
                }
                mBraceCount--;
            }
            else if (currToken->mContent == "{")
            {
                mBraceCount++;
            }
            break;

        case token::IFSTMT:
        {
            toper = tokens[++index];
            if (toper->mContent != "(")
                panic("( after while expected", toper);

            auto condition = this->nextVariable(tokens, &index);
            auto mathVar = dynamic_cast<runtime::MathVar *>(condition);
            if (!mathVar)
                panic("Value cant be used as boolean.", toper);

            if (!this->exceptOperator(")", tokens, &index))
                panic(") excepted after condition", tokens[index]);

            if (!this->exceptOperator("{", tokens, &index))
                panic("{ excepted after condition", tokens[index]);

            mBraceCount++;
            if (!mathVar->as_int())
            {
                mBraceCount--;
                this->skipScope(tokens, &index);
            }
            delete condition;
        }
        break;
        case token::WHILE:
        {
            int jmp = index;
            toper = tokens[++index];
            if (toper->mContent != "(")
                panic("( after while expected", toper);

            auto condition = this->nextVariable(tokens, &index);
            auto mathVar = dynamic_cast<runtime::MathVar *>(condition);
            if (!mathVar)
                panic("Value cant be used as boolean.", toper);

            if (!this->exceptOperator(")", tokens, &index))
                panic(") excepted after condition", tokens[index]);

            if (!this->exceptOperator("{", tokens, &index))
                panic("{ excepted after condition", tokens[index]);

            mBraceCount++;
            if (!mathVar->as_int())
            {
                mBraceCount--;
                this->skipScope(tokens, &index);
            }

            delete condition;
            mStack.push_back({mBraceCount, --jmp});
        }
        break;
        case token::BREAK:
        {
            std::pair<int, int> poped = this->mStack.at(this->mStack.size() - 1);
            this->mStack.pop_back();
            this->mBraceCount = poped.first + (mBraceCount - poped.first);
            skipScope(tokens, &index);
        }
        break;
        case token::CONTINUE:
        {
            std::pair<int, int> poped = this->mStack.at(this->mStack.size() - 1);
            this->mStack.pop_back();
            index = poped.second;
        }
        break;
        }
        index++;
    }
}

void parser::Parser::asign(token::Token *tInvoke, token::Token *tokens[], int *idx)
{
    std::string varName = tInvoke->mContent;
    try
    {
        auto currentVar = this->mVariableMap[varName];
        bool del = this->mVariableMap.find(varName) != this->mVariableMap.end();

        auto newVar = this->nextVariable(tokens, idx);
        newVar->setFree(false);
        this->mVariableMap[varName] = newVar;

        if (del)
            delete currentVar;
    }
    catch (std::exception &err)
    {
        panic(std::string("Invalid assignment at line ")
                  .append(std::to_string(tInvoke->mLine))
                  .append(" -> ")
                  .append(std::string(err.what())),
              tInvoke);
    }
}

runtime::Variable *parser::Parser::funcionCall(token::Token *tInvoke, token::Token *tokens[], int *idx)
{
    std::vector<runtime::Variable *> args;
    int b = 1;
    token::Token *toper = tokens[*idx + b];
    if (!(toper->mType == token::Type::OPERATOR && toper->mContent == ")"))
    {
        while (true)
        {
            args.push_back(this->nextVariable(tokens, idx));
            token::Token *toper = tokens[*idx + b];
            if (toper->mType == token::Type::OPERATOR && toper->mContent == ")")
                break;
            else if (toper->mContent != ",")
            {
                panic("Unexcepted value!", toper);
            }
            *idx += 1;
        }
    }

    if (!exceptOperator(")", tokens, idx))
        panic(") excepted after arguements of function call", tokens[*idx]);

    auto res = this->mFunctionMap.at(tInvoke->mContent)->execute(args);

    for (auto arg : args)
        if (arg->isFree())
            delete arg;

    return res;
}

runtime::Variable *parser::Parser::nextVariable(token::Token *tokens[], int *idx)
{
    return this->nextVariable(tokens, idx, true);
}

runtime::Variable *parser::Parser::evaluateMapOperation(std::map<std::string, std::string> operationMap,
                                                        int *idx, token::Token *potentialOperator,
                                                        token::Token *tokens[], runtime::Variable *var,
                                                        bool allowComparison)
{
    *idx += 1;
    runtime::Variable *secondArg = this->nextVariable(tokens, idx, allowComparison);
    std::string op = operationMap.at(potentialOperator->mContent);
    auto _var = this->mFunctionMap.at(op)
                    ->execute(std::vector<runtime::Variable *>{
                        var,
                        secondArg,
                    });

    if (secondArg->isFree())
        delete secondArg;

    if (var->isFree())
        delete var;

    return _var;
}

runtime::Variable *parser::Parser::nextVariable(token::Token *tokens[], int *idx, bool allowComparison)
{
    auto tval = tokens[*idx + 1];
    runtime::Variable *var = nullptr;
    if (tval->mType == token::INTEGER)
    {
        *idx += 1;
        var = new runtime::Integer(runtime::INTEGER, tval->mContent);
    }
    else if (tval->mType == token::STRING)
    {
        *idx += 1;
        var = new runtime::String(runtime::STRING, tval->mContent);
    }
    else if (tval->mType == token::BOOLEAN)
    {
        *idx += 1;
        var = new runtime::Boolean(tval->mContent);
    }
    else if (tval->mType == token::IDENTIFIER)
    {
        auto toper = tokens[*idx + 2];
        if (this->mVariableMap.find(tval->mContent) != this->mVariableMap.end())
        {
            *idx += 1;
            var = this->mVariableMap.at(tval->mContent);
            runtime::Array *arrayVar = dynamic_cast<runtime::Array *>(var);
            if (tokens[*idx + 1]->mType == token::OPERATOR && tokens[*idx + 1]->mContent == "[")
            {
                *idx += 1;
                runtime::Variable *access = this->nextVariable(tokens, idx);
                runtime::MathVar *mathVar = dynamic_cast<runtime::MathVar *>(access);
                if (!mathVar)
                    panic("Array acces without mathematical var!", tval);

                var = arrayVar->get(mathVar->as_int());
                *idx += 1;
            }
        }
        else if (toper->mType == token::OPERATOR && toper->mContent == "(")
        {
            *idx += 2;
            var = this->funcionCall(tval, tokens, idx);
        }
    }
    else if (tval->mType == token::OPERATOR)
    {
        if (tval->mContent == "[")
        {
            runtime::Array *newArray = new runtime::Array();
            *idx += 1;
            while (true)
            {
                newArray->add(this->nextVariable(tokens, idx));

                if (tokens[*idx + 1]->mType == token::OPERATOR && tokens[*idx + 1]->mContent == "]")
                    break;

                if (!exceptOperator(",", tokens, idx))
                    panic(", expected in list constructor", tokens[*idx]);
            }
            *idx += 1;
            var = newArray;
        }
    }
    if (var == nullptr)
    {
        panic("Invalid value!", tval);
    }
    else
    {
        token::Token *potentialOperator = tokens[*idx + 1];
        if (potentialOperator->mType == token::OPERATOR)
        {
            if (this->mOperatorMap.find(potentialOperator->mContent) != this->mOperatorMap.end())
            {
                var = evaluateMapOperation(this->mOperatorMap, idx, potentialOperator, tokens, var, false);
            }
        }

        token::Token *potentialComparator = tokens[*idx + 1];
        if (potentialComparator->mType == token::OPERATOR && allowComparison)
        {
            if (this->mComparatorMap.find(potentialComparator->mContent) != this->mComparatorMap.end())
            {
                var = evaluateMapOperation(this->mComparatorMap, idx, potentialComparator, tokens, var, false);
            }
        }

        token::Token *bitwiseCond = tokens[*idx + 1];
        if (bitwiseCond->mType == token::OPERATOR && allowComparison)
        {
            if (this->mCondBitwiseMap.find(bitwiseCond->mContent) != this->mCondBitwiseMap.end())
            {
                var = evaluateMapOperation(this->mCondBitwiseMap, idx, bitwiseCond, tokens, var, true);
            }
        }
        return var;
    }
}

bool parser::Parser::exceptOperator(std::string excepted, token::Token *tokens[], int *idx)
{
    *idx += 1;
    auto curr = tokens[*idx];
    return curr->mType == token::OPERATOR && curr->mContent == excepted;
}

void parser::Parser::skipScope(token::Token *tokens[], int *idx)
{
    token::Token *currToken;
    size_t cnt = mBraceCount + 1;
    do
    {
        *idx += 1;
        currToken = tokens[*idx];
        cnt += (currToken->mType == token::OPERATOR) *
               ((currToken->mContent == "{") +
                (-(currToken->mContent == "}")));
    } while (cnt != mBraceCount);
}