#include "slr_table.hpp"
#include <stdexcept>

static bool is_terminal(const Grammar& g, const std::string& s) {
    return g.terminals.count(s) != 0;
}

static void put_action(ActionTable& t, int st, const std::string& a, Action act) {
    auto key = std::make_pair(st, a);
    auto it = t.find(key);
    if (it != t.end()) {
        throw std::runtime_error("SLR conflict at state " + std::to_string(st) + " on '" + a + "'");
    }
    t.emplace(key, act);
}

SLRTable build_slr_table(
    const Grammar& g,
    const LR0DFA& dfa,
    const std::unordered_map<std::string, std::unordered_set<std::string>>& follow
) {
    SLRTable tab;


    // shift/goto
    for (const auto& [key, j] : dfa.trans) {
        int i = key.first;
        const std::string& X = key.second;

        if (X == "$") continue;

        if (is_terminal(g, X)) {
            put_action(tab.action, i, X, Action{ActionType::Shift, j});
        } else {
            tab.go_to[{i, X}] = j;
        }
    }

    //reduce/accept
    for (int i = 0; i < (int)dfa.states.size(); ++i) {
        for (const auto& it : dfa.states[i]) {
            const auto& p = g.prods[it.prod];
            if (it.point != (int)p.rhs.size()) continue;

            if (it.prod == 0) {
                put_action(tab.action, i, "$", Action{ActionType::Accept, 0});
            } else {
                auto f = follow.find(p.lhs);
                if (f == follow.end())
                    throw std::runtime_error("No FOLLOW for " + p.lhs);
                
                for (const auto& a : f->second) {
                    put_action(tab.action, i, a, Action{ActionType::Reduce, it.prod});
                }
            }
        }
    }

    return tab;
}