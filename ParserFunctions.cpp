#include "Parser.hpp"
#include "iostream"

using namespace fastscript;

runtime::LiveFunction *parser::Parser::functionDefinition(token::Token *tokens[], int *idx)
{
    *idx += 1;
    if (this->exceptOperator("(", tokens, idx))
        parser::panic("( expected at function definition", tokens[*idx]);

    std::vector<token::Token *> identifiers;
    while (true)
    {
        if (tokens[*idx]->mType == token::Type::OPERATOR && tokens[*idx]->mContent == ")")
        {
            *idx -= 1;
            break;
        }
        if (tokens[*idx]->mType != token::IDENTIFIER)
            panic("Identifier excepted as function parameter", tokens[*idx]);

        identifiers.push_back(tokens[*idx]);
        token::Token *toper = tokens[*idx + 1];
        if (toper->mType == token::Type::OPERATOR && toper->mContent == ")")
            break;
        else if (toper->mContent != ",")
            panic("Excepted , in parameter list", toper);

        *idx += 2;
    }

    if (!this->exceptOperator(")", tokens, idx))
        panic(") required to end function parameter list ", tokens[*idx]);

    if (!this->exceptOperator("{", tokens, idx))
        panic("{ required to open function", tokens[*idx]);

    this->mBraceCount++;
    int start = *idx;
    this->skipScope(tokens, idx);
    int end = *idx;

    return new runtime::LiveFunction(start, end, identifiers);
}