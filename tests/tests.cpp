#include "grammar.hpp"
#include "lr0.hpp"
#include "slr_table.hpp"
#include "parser.hpp"
#include "lexer.hpp"

#include <cassert>
#include <iostream>

std::unordered_map<std::string, std::unordered_set<std::string>> follow = {
    {"E", {"+", "-", ")", "$"}},
    {"T", {"*", "/", "+", "-", ")", "$"}},
    {"F", {"*", "/", "+", "-", ")", "$"}}
};

static Grammar make_grammar() {
    return make_expr_grammar();
}

static SLRTable make_table(const Grammar& g) {
    auto dfa = build_lr0_dfa(g);
    return build_slr_table(g, dfa, follow);
}

void accept(const std::string& s,
            const Grammar& g,
            const SLRTable& table) {
    auto toks = lex_all(s);
    bool ok = parse_and_trace(g, table, toks);
    assert(ok);
}

void error(const std::string& s,
           const Grammar& g,
           const SLRTable& table) {
    auto toks = lex_all(s);
    bool ok = parse_and_trace(g, table, toks);
    assert(!ok);
}

int main() {
    Grammar g = make_grammar();
    SLRTable table = make_table(g);

    // ---- ACCEPT ----
    accept("a", g, table);
    accept("a+3", g, table);
    accept("(a+3)*b", g, table);
    accept("a+b*c", g, table);
    accept("(a+b)*c", g, table);
    accept("a/b/c", g, table);

    // ---- ERROR ----
    error("", g, table);
    error("+", g, table);
    error("a+", g, table);
    error("(a+3", g, table);
    error("a+3)", g, table);
    error("a**b", g, table);
    error("()", g, table);

    std::cout << "All tests passed\n";
}

