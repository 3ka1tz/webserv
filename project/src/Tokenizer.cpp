#include "../include/Tokenizer.hpp"

#include <cctype>
#include <cstddef>

Tokenizer::Tokenizer(const std::string& input) : text(input), pos(0) {}

Token Tokenizer::next()
{
    skipWhitespace();
    skipComments();
    skipWhitespace();

    if (pos >= text.size())
        return Token(END, "");

    char c = text[pos];

    if (c == '{') { pos++; return Token(LBRACE, "{" ); }
    if (c == '}') { pos++; return Token(RBRACE, "}" ); }
    if (c == ';') { pos++; return Token(SEMICOLON, ";"); }

    return parseWord();
}

void Tokenizer::skipWhitespace()
{
    while (pos < text.size() && std::isspace(text[pos]))
        pos++;
}

void Tokenizer::skipComments()
{
    while (pos < text.size() && text[pos] == '#')
    {
        while (pos < text.size() && text[pos] != '\n')
            pos++;
        skipWhitespace();
    }
}

Token Tokenizer::parseWord()
{
    size_t start = pos;

    while (pos < text.size() &&
           !std::isspace(text[pos]) &&
           text[pos] != '#' &&
           text[pos] != '{' &&
           text[pos] != '}' &&
           text[pos] != ';')
    {
        pos++;
    }

    return Token(WORD, text.substr(start, pos - start));
}
