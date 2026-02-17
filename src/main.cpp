#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "grammar.hpp"
#include "lr0.hpp"
#include "parser.hpp"
#include "lexer.hpp"
#include "slr_table.hpp"

//follow
std::unordered_map<std::string, std::unordered_set<std::string>> follow = {
    {"E", {")", "$"}},
    {"T", {"+", "-", ")", "$"}},
    {"F", {"*", "/", "+", "-", ")", "$"}}
};

int main() {
    Grammar g = make_expr_grammar();
    auto dfa = build_lr0_dfa(g);

    auto tab = build_slr_table(g, dfa, follow);

    std::string s;
    std::getline(std::cin, s);
    auto tokens = lex_all(s);

    bool ok = parse_and_trace(g, tab, tokens);
    return ok ? 0 : 1;
}