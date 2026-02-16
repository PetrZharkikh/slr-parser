#include "grammar.hpp"

Grammar make_expr_grammar() {
    Grammar g;
    g.start = "E";
    g.augumented_start = "S";

    g.prods.push_back({"S'", {"E"}});

    g.prods.push_back({"E", {"E", "+", "T"}});
    g.prods.push_back({"E", {"E", "-", "T"}});
    g.prods.push_back({"E", {"T"}});

    g.prods.push_back({"T", {"T", "*", "F"}});
    g.prods.push_back({"T", {"T", "/", "F"}});
    g.prods.push_back({"T", {"F"}});

    g.prods.push_back({"F", {"(", "E", ")"}});
    g.prods.push_back({"T", {"id"}});
    g.prods.push_back({"T", {"num"}});

    g.terminals = {"+", "-", "*", "/", "(", ")", "id", "num", "$"};
    g.nonterminals = {"E", "S'", "F", "T"};

    return g;
}