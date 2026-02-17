#include "parser.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

static std::string tok_to_term(const Token& t) {
    switch (t.type) {
        case token_type::ID: return "id";
        case token_type::NUM: return "num";
        case token_type::PLUS: return "+";
        case token_type::MINUS: return "-";
        case token_type::MUL: return "*";
        case token_type::DIV: return "/";
        case token_type::LPAREN: return "(";
        case token_type::RPAREN: return ")";
        case token_type::END: return "$";
        default: return "??";
    }
}

static std::string stack_to_string(const std::vector<StackEntry>& st) {
    std::ostringstream oss;
    for (const auto& e : st) oss << e.sym;
    return oss.str();
}

static std::string input_to_string(const std::vector<Token>& toks, size_t pos) {
    std::ostringstream oss;
    for (size_t i = pos; i < toks.size(); ++i) oss << tok_to_term(toks[i]);
    return oss.str();
}

static std::string prod_to_string(const Production& p) {
    std::ostringstream oss;
    oss << p.lhs << " -> ";
    for (auto& x : p.rhs) oss << x << " ";
    return oss.str();
}

bool parse_and_trace(
    const Grammar& g,
    const SLRTable& tab,
    const std::vector<Token>& tokens
) {
    std::vector<StackEntry> st;
    st.push_back({"$", 0});

    size_t pos = 0;

    constexpr int W_STACK = 18;
    constexpr int W_INPUT = 22;

    std::cout << std::left
              << std::setw(W_STACK) << "STACK"
              << std::setw(W_INPUT) << "INPUT"
              << "ACTION\n";

    while (true) {
        int s = st.back().state;
        std::string a = tok_to_term(tokens[pos]);

        Action act{ActionType::Error, -1};
        auto it = tab.action.find({s, a});
        if (it != tab.action.end()) act = it->second;

        std::cout << std::left
                  << std::setw(W_STACK) << stack_to_string(st)
                  << std::setw(W_INPUT) << input_to_string(tokens, pos);

        switch (act.type) {

        case ActionType::Shift: {
            std::cout << "shift " << act.value << "\n";
            st.push_back({a, act.value});
            ++pos;
            break;
        }

        case ActionType::Reduce: {
            const auto& p = g.prods[act.value];
            std::cout << "reduce " << prod_to_string(p) << "\n";

            for (int k = 0; k < (int)p.rhs.size(); ++k) st.pop_back();

            int s2 = st.back().state;
            auto git = tab.go_to.find({s2, p.lhs});
            if (git == tab.go_to.end()) {
                std::cout << "error (no goto)\n";
                return false;
            }

            st.push_back({p.lhs, git->second});
            break;
        }

        case ActionType::Accept: {
            if (a != "$") {
                std::cout << "error (accept on non-$)\n";
                return false;
            }
            std::cout << "accept\n";
            return true;
        }

        case ActionType::Error:
        default:
            std::cout << "error\n";
            return false;
        }
    }
}