#include <map>
#include <iostream>
#include "Parser.hpp"
#include "runtime/Variables/Variable.hpp"
#include "runtime/Functions/PrintFunction.hpp"
#include "runtime/Functions/MathFunctions.hpp"

using namespace fastscript;

void panic(std::string str, token::Token *tval)
{
    std::cout << token::T_CANONICAL[tval->mType]
              << " " << tval->mContent << " l: "
              << tval->mLine << std::endl;
    throw std::runtime_error(str);
}

void parser::Parser::parse(std::vector<token::Token *> program)
{
    this->mFunctionMap["print"] = new runtime::PrintFunction();
    this->mFunctionMap["add"] = new runtime::Add();
    this->mFunctionMap["multiply"] = new runtime::Multiply();
    this->mFunctionMap["divide"] = new runtime::Divide();
    this->mFunctionMap["subtract"] = new runtime::Subtract();

    token::Token *currToken;
    token::Token *tokens[program.capacity()];
    std::copy(program.begin(), program.end(), tokens);
    int index = 0;
    while (index < program.capacity())
    {
        currToken = tokens[index];
        switch (currToken->mType)
        {
        case token::IDENTIFIER:
            auto toper = tokens[++index];
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
        }
        index++;
    }
}

void parser::Parser::asign(token::Token *tInvoke, token::Token *tokens[], int *idx)
{

    auto tval = tokens[*idx + 1];

    try
    {
        this->mVariableMap[tInvoke->mContent] = this->nextVariable(tInvoke, tokens, idx);
    }
    catch (std::exception &err)
    {
        panic(std::string("Invalid assignment at line ")
                  .append(std::to_string(tval->mLine))
                  .append(" -> ")
                  .append(std::string(err.what())),
              tInvoke);
    }
}

runtime::Variable *parser::Parser::funcionCall(token::Token *tInvoke, token::Token *tokens[], int *idx)
{
    std::vector<runtime::Variable *> args;
    int b = 1;
    while (true)
    {
        token::Token *toper = tokens[*idx + b];
        args.push_back(this->nextVariable(toper, tokens, idx));
        toper = tokens[*idx + b];
        if (toper->mType == token::Type::OPERATOR && toper->mContent == ")")
            break;
        b++;
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
    else if (tval->mType == token::IDENTIFIER)
    {
        auto toper = tokens[*idx + 1];
        if (this->mVariableMap.find(tval->mContent) != this->mVariableMap.end())
        {
            *idx += 1;
            var = this->mVariableMap.at(tval->mContent);
        }
        else if (toper->mType == token::OPERATOR && toper->mContent == "(")
        {
            *idx += 1;
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
            std::string op;
            if (potentialOperator->mContent == "+")
            {
                op = "add";
            }
            else if (potentialOperator->mContent == "*")
            {
                op = "multiply";
            }
            else if (potentialOperator->mContent == "-")
            {
                op = "subtract";
            }
            else if (potentialOperator->mContent == "/")
            {
                op = "divide";
            }
            if (!op.empty())
            {
                *idx += 1;
                runtime::Variable *secondArg = this->nextVariable(potentialOperator, tokens, idx);
                
                auto _var = this->mFunctionMap.at(op)->execute(std::vector<runtime::Variable *>{
                    var,
                    secondArg,
                });
                delete var;
                var = _var;
            }
        }
        return var;
    }
}