#pragma once
#include <string>
#include <vector>
#include <unordered_set>

struct Production{
    std::string lhs;
    std::vector<std::string> rhs;
};

struct Grammar{
    std::string start;
    std::string augumented_start;
    std::vector<Production> prods;

    std::unordered_set<std::string> terminals;
    std::unordered_set<std::string> nonterminals;
};

Grammar make_expr_grammar();

