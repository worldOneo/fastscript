#include <iostream>
#include <iomanip>
#include "Tokenizer.hpp"
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
        size_t fileSize = ftell(fh) + 1;
        fseek(fh, 0, SEEK_SET);
        std::string fileContents(fileSize, ' ');
        fread((void *)fileContents.data(), 1, fileSize, fh);

        token::Tokenizer tokenizer;
        std::vector<token::Token *> tokens = tokenizer.parse(fileContents);

        /*int i = 0;
        for (auto parsed_token : tokens)
        {
            std::cout << std::setw(5) << i++ << std::setw(20)
                      << token::T_CANONICAL[parsed_token->mType] << std::setw(20)
                      << parsed_token->mContent << std::setw(20)
                      << parsed_token->mLine << std::setw(9)
                      << parsed_token->mHeatedContent << std::endl;
        }
        std::cout << std::setw(0);*/

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