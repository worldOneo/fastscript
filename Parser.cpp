#include <map>
#include <iostream>
#include "Parser.hpp"
#include "runtime/Variables/Variable.hpp"
#include "runtime/Functions/PrintFunction.hpp"
#include "runtime/Functions/MathFunctions.hpp"
#include "runtime/Functions/Compare.hpp"

using namespace fastscript;

void panic(std::string str, token::Token *tval)
{
    std::cout << token::T_CANONICAL[tval->mType]
              << " " << tval->mContent << " line: "
              << tval->mLine << std::endl;
    throw std::runtime_error(str);
}

parser::Parser::Parser()
{
    this->mFunctionMap["print"] = new runtime::PrintFunction();
    this->mFunctionMap["printf"] = new runtime::PrintFormatedFunction();
    this->mFunctionMap["boolean"] = new runtime::AsBoolean();

    this->mFunctionMap["add"] = new runtime::Add();
    this->mFunctionMap["subtract"] = new runtime::Subtract();
    this->mFunctionMap["multiply"] = new runtime::Multiply();
    this->mFunctionMap["divide"] = new runtime::Divide();
    this->mFunctionMap["xor"] = new runtime::LogicXOR();
    this->mFunctionMap["and"] = new runtime::LogicAND();
    this->mFunctionMap["or"] = new runtime::LogicOR();
    this->mFunctionMap["rshft"] = new runtime::LogicRSHFT();
    this->mFunctionMap["lshft"] = new runtime::LogicLSHFT();
    this->mFunctionMap["equal"] = new runtime::LogicEQ();
    this->mFunctionMap["gt"] = new runtime::LogicGT();
    this->mFunctionMap["lt"] = new runtime::LogicLT();
    this->mFunctionMap["gteq"] = new runtime::LogicGTEQ();
    this->mFunctionMap["lteq"] = new runtime::LogicLTEQ();

    this->mOperatorMap["+"] = "add";
    this->mOperatorMap["-"] = "subtract";
    this->mOperatorMap["*"] = "multiply";
    this->mOperatorMap["/"] = "divide";
    this->mOperatorMap["^"] = "xor";
    this->mOperatorMap["|"] = "or";
    this->mOperatorMap["&"] = "and";
    this->mOperatorMap["<<"] = "lshft";
    this->mOperatorMap[">>"] = "rshft";
    this->mOperatorMap[">>"] = "rshft";
    this->mOperatorMap["=="] = "equal";
    this->mOperatorMap[">"] = "gt";
    this->mOperatorMap["<"] = "lt";
    this->mOperatorMap["<="] = "lteq";
    this->mOperatorMap[">="] = "gteq";
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
                break;
            }
            break;
        case token::OPERATOR:
            // TODO: Jumping on the stack
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

            auto condition = this->nextVariable(currToken, tokens, &index);
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
                do
                {
                    currToken = tokens[++index];
                } while (!(currToken->mType == token::OPERATOR && currToken->mContent == "}"));
                break;
            }
        }
        break;
        case token::WHILE:
        {
            int jmp = index;
            toper = tokens[++index];
            if (toper->mContent != "(")
                panic("( after while expected", toper);

            auto condition = this->nextVariable(currToken, tokens, &index);
            auto mathVar = dynamic_cast<runtime::MathVar *>(condition);
            if (!mathVar)
                panic("Value cant be used as boolean.", toper);

            if (!this->exceptOperator(")", tokens, &index))
                panic(") excepted after condition", tokens[index]);

            if (!this->exceptOperator("{", tokens, &index))
                panic("{ excepted after condition", tokens[index]);

            if (!mathVar->as_int())
            {
                do
                {
                    currToken = tokens[++index];
                } while (!(currToken->mType == token::OPERATOR && currToken->mContent == "}"));
                break;
            }

            mBraceCount++;
            mStack.push_back({mBraceCount, --jmp});
        }
        break;
        }
        index++;
    }
}

void parser::Parser::asign(token::Token *tInvoke, token::Token *tokens[], int *idx)
{
    try
    {
        this->mVariableMap[tInvoke->mContent] = this->nextVariable(tInvoke, tokens, idx);
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
            token::Token *toper = tokens[*idx + b];
            args.push_back(this->nextVariable(toper, tokens, idx));
            toper = tokens[*idx + b];
            if (toper->mType == token::Type::OPERATOR && toper->mContent == ")")
                break;
            else if (toper->mContent != ",")
            {
                panic("Unexcepted value!", toper);
            }
            *idx += 1;
        }
    }

    return this->mFunctionMap.at(tInvoke->mContent)->execute(args);
}

runtime::Variable *parser::Parser::nextVariable(token::Token *tInvoke, token::Token *tokens[], int *idx)
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
        }
        else if (toper->mType == token::OPERATOR && toper->mContent == "(")
        {
            *idx += 2;
            var = this->funcionCall(tval, tokens, idx);
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
                *idx += 1;
                runtime::Variable *secondArg = this->nextVariable(potentialOperator, tokens, idx);
                std::string op = this->mOperatorMap.at(potentialOperator->mContent);
                var = this->mFunctionMap.at(op)
                          ->execute(std::vector<runtime::Variable *>{
                              var,
                              secondArg,
                          });
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