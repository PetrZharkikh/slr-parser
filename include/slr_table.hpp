#pragma once 
#include "grammar.hpp"
#include "lr0.hpp"
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>

enum class ActionType {Shift, Reduce, Accept, Error};

struct Action {
    ActionType type = ActionType::Error;
    int value = -1;
};

using ActionTable = std::map<std::pair<int, std::string>, Action>;
using GotoTable = std::map<std::pair<int, std::string>, int>;

struct SLRTable {
    ActionTable action;
    GotoTable go_to;
};

SLRTable build_slr_table(
    const Grammar& g,
    const LR0DFA& dfa,
    const std::unordered_map<std::string, std::unordered_set<std::string>>& follow
);