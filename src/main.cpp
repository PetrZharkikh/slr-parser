#include <iostream>
#include "grammar.hpp"
#include "lr0.hpp"

static void print_itemset(const Grammar& g, const ItemSet& I) {
    for (const auto& it : I) {
        const auto& p = g.prods[it.prod];
        std::cout << p.lhs << " -> ";
        for (int i = 0; i < (int)p.rhs.size(); ++i) {
            if (i == it.point) std::cout << "• ";
            std::cout << p.rhs[i] << " ";
        }
        if (it.point == (int)p.rhs.size()) std::cout << "•";
        std::cout << "\n";
    }
}

int main() {
    Grammar g = make_expr_grammar();
    LR0DFA dfa = build_lr0_dfa(g);

    for (int i = 0; i < (int)dfa.states.size(); ++i) {
        std::cout << "\n=== I" << i << " ===\n";
        print_itemset(g, dfa.states[i]);
    }

    std::cout << "\n=== transitions ===\n";
    for (const auto& [key, to] : dfa.trans) {
        std::cout << "I" << key.first << " -- " << key.second
                  << " --> I" << to << "\n";
    }

    return 0;
}
