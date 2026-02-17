#include "lr0.hpp"
#include <queue>

ItemSet closure(const Grammar& g, const ItemSet& I) {
    ItemSet result = I;
    bool changed = true;

    while (changed) {
        changed = false;
        for (const auto& item : result) {
            const auto& prod = g.prods[item.prod];

            if (item.prod >= (int)prod.rhs.size())
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