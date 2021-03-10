#include "Tokens.hpp"
#include "iostream"

using namespace fastscript::token;

std::vector<Token *> Tokenizer::parse(std::string &script)
{
    std::vector<Token *> tokenized;
    Token *token = new Token();
    int lineCount = 1;
    token->mLine = lineCount;
    for (char curr : script)
    {
        switch (curr)
        {

        case '\n':
            lineCount++;
        case '\r':
            lineCount++;
        case ' ':
        case '\t':
            if (token->mType == STRING)
            {
                token->mContent.append(sizeof(curr), curr);
                break;
            }
            if (token->mType != WHITESPACE)
            {
                tokenized.push_back(token);
                token = new Token();
                token->mLine = lineCount;
            }
            token->mType = WHITESPACE;
            break;

        case '0' ... '9':
            if (token->mType == IDENTIFIER || token->mType == STRING)
            {
                token->mContent.push_back(curr);
            }
            else if (token->mType == WHITESPACE || token->mType == INTEGER)
            {
                token->mType = INTEGER;
                token->mContent.push_back(curr);
            }
            break;
        case 'A' ... 'z':
            if (token->mType == OPERATOR)
            {
                tokenized.push_back(token);
                token = new Token();
                token->mType = IDENTIFIER;
                token->mContent.append(sizeof(curr), curr);
                token->mLine = lineCount;
            }
            else if (token->mType == WHITESPACE)
            {
                token->mType = IDENTIFIER;
                token->mContent.append(sizeof(curr), curr);
            }
            else if (token->mType == IDENTIFIER || token->mType == STRING)
            {
                token->mContent.append(sizeof(curr), curr);
            }
            break;
        case '(' ... '/': //()*+,-./
        case '{':
        case '}':
        case ':' ... '?': //:;<>=?
            if (token->mType == STRING)
            {
                token->mContent.append(sizeof(curr), curr);
                break;
            }
            if (token->mType != WHITESPACE)
                tokenized.push_back(token);
            token = new Token();
            token->mType = OPERATOR;
            token->mContent.append(sizeof(curr), curr);
            token->mLine = lineCount;
            break;
        case '"':
            if (token->mType == STRING)
            {
                tokenized.push_back(token);
                token = new Token();
                token->mLine = lineCount;
                token->mType = WHITESPACE;
                break;
            }
            if (token->mType != WHITESPACE)
                tokenized.push_back(token);
            token = new Token();
            token->mLine = lineCount;
            token->mType = STRING;
            break;
        default:
            if (token->mType == STRING)
            {
                token->mContent.append(sizeof(curr), curr);
                break;
            }
        }
    }
    return tokenized;
}