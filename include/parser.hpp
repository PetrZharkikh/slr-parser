#pragma once
#include "grammar.hpp"
#include "slr_table.hpp"
#include "token.hpp"
#include <vector>
#include <string>

bool parse_and_trace(
    const Grammar& g,
    const SLRTable& tab,
    const std::vector<Token>& tokens
);