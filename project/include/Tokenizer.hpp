#pragma once

#include <string>

enum TokenType
{
    WORD,
    LBRACE,
    RBRACE,
    SEMICOLON,
    END
};

struct Token
{
    TokenType type;
    std::string value;
};

class Tokenizer
{
    public:
        Tokenizer(const std::string& input);
        Token next();

    private:
        std::string text;
        size_t pos;

        void skipWhitespace();
        void skipComments();
        Token parseWord();
};
