#pragma once
#include <string>
#include <vector>
#include <unordered_set>

//one production rule lhs -> rhs
struct Production{
    std::string lhs;
    std::vector<std::string> rhs;
};

//grammar description: set of productions, terminals and non-terminals
struct Grammar{
    std::string start;              //start symbol
    std::string augumented_start;   //augumented start symbol like S'
    std::vector<Production> prods;

    std::unordered_set<std::string> terminals;
    std::unordered_set<std::string> nonterminals;
};

Grammar make_expr_grammar();

