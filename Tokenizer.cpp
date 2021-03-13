#include "Tokenizer.hpp"
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
                token->mHeatedContent = token->mContent == "true";
            }
            else if (token->mContent == "if")
            {
                token->mType = IFSTMT;
                token->mContent.erase();
            }
            else if (token->mContent == "break")
            {
                token->mType = BREAK;
                token->mContent.erase();
            }
            else if (token->mContent == "while")
            {
                token->mType = WHILE;
                token->mContent.erase();
            }
            else if (token->mContent == "continue")
            {
                token->mType = CONTINUE;
                token->mContent.erase();
            }
        }
        else if (token->mType == OPERATOR)
        {
            if (token->mContent.size() == 1)
            {
                token->mHeatedContent = token->mContent.at(0);
            }
            else
            {
                token->mHeatedContent = (((short)token->mContent.at(0)) << 8) | (0x00ff & token->mContent.at(1));
            }
            token->mContent.erase();
        }
        else if (token->mType == INTEGER)
        {
            token->mHeatedContent = std::stoi(token->mContent);
            token->mContent.erase();
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
            if (token->mType == IDENTIFIER || token->mType == STRING || token->mType == DOUBLE)
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
        case '_':
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
        case '%' ... '&':
        case '|':
        case '[' ... '^': // [\]^
        case '{':
        case '}':
        case ':' ... '?': //:;<>=?
        case '#':
        case '$':
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
                    (curr == '>' && token->mContent == ">") ||
                    (curr == '&' && token->mContent == "&") ||
                    (curr == '|' && token->mContent == "|"))
                {
                    token->mContent.append(sizeof(curr), curr);
                    break;
                }
            }
            if (token->mType == INTEGER)
            {
                if (curr == '.')
                {
                    if (token->mContent.find('.') == std::string::npos)
                    {
                        token->mType = DOUBLE;
                        token->mContent.append(sizeof(curr), curr);
                        break;
                    }
                    else
                    {
                        std::string err = std::string("Cant tokenize double value at line: ")
                                              .append(std::to_string(token->mLine));
                        throw std::runtime_error(err);
                    }
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