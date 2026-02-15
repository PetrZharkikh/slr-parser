#pragma once
#include <string>

enum class token_type {
    ID, NUM,
    PLUS, MINUS, MUL, DIV,
    LPAREN, RPAREN,
    END,
    INVALI
};

struct Token {
    token_type type{};
    std::string lexeme;
};

