#include "grammar.hpp"

//builds grammar for arithmetic expressions
//used both in main program and in tests

Grammar make_expr_grammar() {
    Grammar g;
    g.start = "E";
    g.augumented_start = "S'";

    g.prods.push_back({"S'", {"E"}});

    g.prods.push_back({"E", {"E", "+", "T"}});
    g.prods.push_back({"E", {"E", "-", "T"}});
    g.prods.push_back({"E", {"T"}});

    g.prods.push_back({"T", {"T", "*", "F"}});
    g.prods.push_back({"T", {"T", "/", "F"}});
    g.prods.push_back({"T", {"F"}});

    g.prods.push_back({"F", {"(", "E", ")"}});
    g.prods.push_back({"F", {"id"}});
    g.prods.push_back({"F", {"num"}});

    g.terminals = {"+", "-", "*", "/", "(", ")", "id", "num", "$"};
    g.nonterminals = {"E", "S'", "F", "T"};

    return g;
}