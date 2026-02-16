#include "lexer.hpp"
#include <cctype>

static Token make(token_type t, std::string s) { return Token{t, std::move(s)}; }

std::vector<Token> lex_all(const std::string& input) {
    std::vector<Token> out;
    size_t i = 0;
    auto peek = [&]() -> char {return i < input.size() ? input[i] : '\0'; };
    while (i < input.size()) {
        char c = peek();

        if (std::isspace(static_cast<unsigned char>(c))) { ++i; continue; }

        if (std::isalpha(static_cast<unsigned char>(c))) {
            size_t j = i;
            while (j < input.size() && std::isalpha(static_cast<unsigned char>(input[j]))) ++j;
            out.push_back(make(token_type::ID, input.substr(i, j - i)));
            i = j;
            continue;
        }

        if (std::isdigit(static_cast<unsigned char>(c))) {
            size_t j = i;
            while (j < input.size() && std::isdigit(static_cast<unsigned char>(input[j]))) ++j;
            out.push_back(make(token_type::NUM, input.substr(i, j - i)));
            i = j;
            continue;
        }

        switch(c) {
            case '+': out.push_back(make(token_type::PLUS, "+")); ++i; break;
            case '-': out.push_back(make(token_type::MINUS, "-")); ++i; break;
            case '*': out.push_back(make(token_type::MUL, "*")); ++i; break;
            case '/': out.push_back(make(token_type::DIV, "/")); ++i; break;
            case '(': out.push_back(make(token_type::LPAREN, "(")); ++i; break;
            case ')': out.push_back(make(token_type::RPAREN, ")")); ++i; break;
            default:
                out.push_back(make(token_type::INVALID, std::string(1,c)));
                ++i;
                break;
        }
    }

    out.push_back(make(token_type::END, " "));
    return out;
};