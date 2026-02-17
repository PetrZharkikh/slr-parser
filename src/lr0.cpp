#include "lr0.hpp"
#include <queue>

ItemSet closure(const Grammar& g, const ItemSet& I) {
    ItemSet result = I;
    bool changed = true;

    while (changed) {
        changed = false;
        for (const auto& item : result) {
            const auto& prod = g.prods[item.prod];

            if (item.point >= (int)prod.rhs.size())
                continue;
            
            const std::string& sym = prod.rhs[item.point];

            if (g.nonterminals.count(sym)) {
                for (int i = 0; i < (int)g.prods.size(); ++i) {
                    if (g.prods[i].lhs == sym) {
                        Item new_item{i, 0};
                        if (!result.count(new_item)) {
                            result.insert(new_item);
                            changed = true;
                        }
                    }
                }
            }
        }
    }
    return result;
}

ItemSet go_to(const Grammar& g, const ItemSet& I, const std::string& X) {
    ItemSet moved;

    for (const auto& item :I) {
        const auto& p = g.prods[item.prod];

        if (item.point >= (int)p.rhs.size())
            continue;
    
        if (p.rhs[item.point] == X) {
            moved.insert(Item{item.prod, item.point + 1});
        }
    }

    if (moved.empty())
        return moved;

    return closure(g, moved);
}

static int find_state(const std::vector<ItemSet>& states, const ItemSet& s) {
    for (int i = 0; i < (int)states.size(); ++i) {
        if (states [i] == s)
            return i;
    }
    return -1;
}

LR0DFA build_lr0_dfa(const Grammar& g) {
    LR0DFA dfa;

    ItemSet start;
    start.insert(Item{0, 0});
    dfa.states.push_back(closure(g, start));

    std::queue<int> q;
    q.push(0);

    std::vector<std::string> symbols;
    symbols.insert(symbols.end(), g.terminals.begin(), g.terminals.end());
    symbols.insert(symbols.end(), g.nonterminals.begin(), g.nonterminals.end());

    while (!q.empty()) {
        int i = q.front();
        q.pop();

        for (const auto& X : symbols) {
            if (X == "$") continue;

            ItemSet J = go_to(g, dfa.states[i], X);
            if (J.empty()) continue;

            int j = find_state(dfa.states, J);
            if (j == -1) {
                j = (int)dfa.states.size();
                dfa.states.push_back(J);
                q.push(j);
            }

            dfa.trans[{i, X}] = j;
        }
    }

    return dfa;
}