#pragma once
#include <vector>
#include <string>

namespace fastscript::token
{
    enum Type
    {
        WHITESPACE,
        INTEGER,
        IDENTIFIER,
        STRING,
        OPERATOR,
        BOOLEAN,
    };

    static const char *T_CANONICAL[] = {
        "WHITESPACE",
        "INTEGER",
        "IDENTIFIER",
        "STRING",
        "OPERATOR",
        "BOOLEAN"
    };

    class Token
    {
    public:
        enum Type mType;
        std::string mContent;
        int mLine;
    };

    class Tokenizer
    {
    public:
        std::vector<Token *> parse(std::string &script);
    };
}