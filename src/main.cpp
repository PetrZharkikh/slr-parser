#include <iostream>
#include "lexer.hpp"

static const char* to_str(token_type t) {
    switch(t){
        case token_type::ID: return "ID";
        case token_type::NUM: return "NUM";
        case token_type::PLUS: return "PLUS";
        case token_type::MINUS: return "MINUS";
        case token_type::MUL: return "MUL";
        case token_type::DIV: return "DIV";
        case token_type::LPAREN: return "LPAREN";
        case token_type::RPAREN: return "RPAREN";
        case token_type::END: return "END";

        default: return "INVALID";
    }
}

int main() {
    std::string s;
    std::getline(std::cin, s);

    auto tokens = lex_all(s);
    for (const auto& tok : tokens) {
        std::cout << to_str(tok.type) << " '" << tok.lexeme << "'\n";
    }

    return 0;
}
