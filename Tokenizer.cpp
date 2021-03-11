#include "Tokens.hpp"
#include "iostream"

using namespace fastscript::token;

void endToken(std::vector<Token *> &tokenized, Token *&token)
{
    if (token->mType != WHITESPACE)
    {
        if (token->mType == IDENTIFIER)
        {
            if (token->mContent == "true" || token->mContent == "false")
            {
                token->mType = BOOLEAN;
            }
            else if (token->mContent == "if")
            {
                token->mType = IFSTMT;
            }
            else if (token->mContent == "break")
            {
                token->mType = BREAK;
            }
        }
        tokenized.push_back(token);
    }
    else
        delete token;
    token = new Token();
}

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
        case '\r':
        case ' ':
        case '\t':
            lineCount += (curr == '\n') || (curr == '\r');
            if (token->mType == STRING)
            {
                token->mContent.append(sizeof(curr), curr);
                break;
            }
            if (token->mType != WHITESPACE)
            {
                endToken(tokenized, token);
                token->mLine = lineCount;
            }
            token->mType = WHITESPACE;
            break;

        case '0' ... '9':
            if (token->mType == IDENTIFIER || token->mType == STRING)
            {
                token->mContent.push_back(curr);
                break;
            }
            if (token->mType == OPERATOR)
            {
                endToken(tokenized, token);
                token->mLine = lineCount;
            }
            token->mType = INTEGER;
            token->mContent.push_back(curr);
            break;
        case 'A' ... 'Z':
        case 'a' ... 'z':
            if (token->mType == OPERATOR)
            {
                endToken(tokenized, token);
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
        case '&':
        case '|':
        case '[' ... '^': // [\]^
        case '{':
        case '}':
        case ':' ... '?': //:;<>=?
            if (token->mType == STRING)
            {
                token->mContent.append(sizeof(curr), curr);
                break;
            }
            if (token->mType == OPERATOR)
            {
                if ((curr == '=' && token->mContent == "=") ||
                    (curr == '=' && token->mContent == ">") ||
                    (curr == '=' && token->mContent == "<") ||
                    (curr == '<' && token->mContent == "<") ||
                    (curr == '>' && token->mContent == ">"))
                {
                    token->mContent.append(sizeof(curr), curr);
                    break;
                }
            }
            endToken(tokenized, token);
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
            endToken(tokenized, token);
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