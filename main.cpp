#include <iostream>
#include "Tokens.hpp"
#include "Parser.hpp"

using namespace fastscript;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Input file required." << std::endl;
        return 1;
    }
    try
    {
        FILE *fh = fopen(argv[1], "r");
        if (!fh)
        {
            std::cerr << "Can't find file." << std::endl;
            return 1;
        }
        fseek(fh, 0, SEEK_END);
        size_t fileSize = ftell(fh);
        fseek(fh, 0, SEEK_SET);
        std::string fileContents(fileSize, ' ');
        fread(fileContents.data(), 1, fileSize, fh);

        token::Tokenizer tokenizer;
        std::vector<token::Token *> tokens = tokenizer.parse(fileContents);
        for (auto parsed_token : tokens)
        {
            std::cout << token::T_CANONICAL[parsed_token->mType]
                      << " " << parsed_token->mContent << " l: "
                      << parsed_token->mLine << std::endl;
        }
        parser::Parser parser;
        parser.parse(tokens);
    }
    catch (std::exception &err)
    {
        std::cerr << "Error: " << err.what() << std::endl;
        return 2;
    }
    catch (...)
    {
        std::cerr << "Unknown Error." << std::endl;
        return 1;
    }

    return 0;
}