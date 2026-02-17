#pragma once
#include "grammar.hpp"
#include <set>
#include <string>
#include <vector>
#include <map>
#include <utility>

struct Item {
    int prod;   //индекс правила в Grammar::prods
    int point;  //индекс точки

    bool operator<(const Item& other) const {
        if (prod != other.prod) return prod < other.prod;
        return point < other.point;
    }

    bool operator==(const Item& other) const {
        return prod == other.prod && point == other.point;
    }
};

using ItemSet = std::set<Item>;

struct LR0DFA {
    std::vector<ItemSet> states;
    std::map<std::pair<int, std::string>, int> trans;
};

ItemSet closure(const Grammar& g, const ItemSet& I);
ItemSet go_to(const Grammar& g, const ItemSet& I, const std::string& X);
LR0DFA build_lr0_dfa(const Grammar& g);

