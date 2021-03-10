#include <map>
#include <iostream>
#include "Parser.hpp"
#include "runtime/Variables/Variable.hpp"
#include "runtime/Functions/PrintFunction.hpp"

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
    token::Token *currToken;
    token::Token *tokens[program.capacity()];
    std::copy(program.begin(), program.end(), tokens);
    int index = 0;
    while (index < program.capacity())
    {
        currToken = tokens[index];
        /*std::cout << token::T_CANONICAL[currToken->mType]
                  << " " << currToken->mContent << " l: "
                  << currToken->mLine << std::endl;*/
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

    try {
        this->mVariableMap[tInvoke->mContent] = this->nextVariable(tInvoke, tokens, idx);
    } catch (std::exception& ignored) {
        panic("Invalid assignment at line " + std::to_string(tval->mLine), tInvoke);
    }
}

runtime::Variable *parser::Parser::funcionCall(token::Token *tInvoke, token::Token *tokens[], int *idx)
{
    std::vector<runtime::Variable *> args;
    int b = 1;
    while (true)
    {
        token::Token *toper = tokens[*idx + b];
        if (toper->mType == token::Type::OPERATOR && toper->mContent == ")")
            break;
        args.push_back(this->nextVariable(toper, tokens, idx));
        b++;
    }

    return this->mFunctionMap.at(tInvoke->mContent)->execute(args);
}

runtime::Variable *parser::Parser::nextVariable(token::Token *tInvoke, token::Token *tokens[], int *idx)
{
    auto tval = tokens[*idx + 1];
    if (tval->mType == token::INTEGER)
    {
        return new runtime::Integer(runtime::INTEGER, tval->mContent);
    }
    else if (tval->mType == token::STRING)
    {
        return new runtime::String(runtime::STRING, tval->mContent);
    }
    else if (tval->mType == token::IDENTIFIER)
    {
        if (this->mVariableMap.find(tval->mContent) != this->mVariableMap.end())
        {
            return this->mVariableMap.at(tval->mContent);
        }
        else
        {
            std::cout << "Variable " << tval->mContent << " not found " << std::endl;
            auto it = this->mVariableMap.begin();
            while (it != this->mVariableMap.end())
            {
                std::cout << it->first << " :: " << it->second << std::endl;
                it++;
            }
        }
        auto toper = tokens[*idx + 1];
        if (toper->mType == token::OPERATOR && toper->mContent == "(")
        {
            *idx += 1;
            return this->funcionCall(tval, tokens, idx);
        }
    }
    panic("Invalid value!", tval);
}