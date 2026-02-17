#include <iostream>
#include "grammar.hpp"
#include "lr0.hpp"

int main() {
    Grammar g = make_expr_grammar();

    ItemSet start;
    start.insert({0, 0});

    ItemSet c = closure(g, start);

    for (const auto& it : c) {
        const auto& p = g.prods[it.prod];
        std::cout << p.lhs << " -> ";
        for (int i = 0; i < (int)p.rhs.size(); ++i) {
            if (i == it.point) std::cout << "•";
            std::cout << p.rhs[i] << " ";
        }
        if (it.point == (int)p.rhs.size()) std::cout << "•";
        std::cout << "\n";
    }

    return 0;
}
