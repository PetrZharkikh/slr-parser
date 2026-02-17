%option c++ noyywrap nodefault

%{
#include "lexer.hpp"
#include <sstream>

// будем класть результат в статический токен, который читает lex_all
static Token g_tok;
%}

WS      [ \t\r\n]+
ID      [a-zA-Z]+
NUM     [0-9]+

%%

{WS}            { /* skip */ }

"("   { g_tok = {token_type::LPAREN, "("}; return 1; }
")"   { g_tok = {token_type::RPAREN, ")"}; return 1; }
"+"   { g_tok = {token_type::PLUS, "+"};   return 1; }
"-"   { g_tok = {token_type::MINUS, "-"};  return 1; }
"*"   { g_tok = {token_type::MUL, "*"};    return 1; }
"/"   { g_tok = {token_type::DIV, "/"};    return 1; }

{ID}  { g_tok = {token_type::ID, YYText()};  return 1; }
{NUM} { g_tok = {token_type::NUM, YYText()}; return 1; }

<<EOF>> { g_tok = {token_type::END, ""}; return 0; }

. { g_tok = {token_type::INVALID, YYText()}; return 1; }

%%

// Реализуем lex_all прямо в сгенерированном .cpp (после второго %%)
std::vector<Token> lex_all(const std::string& input) {
    std::istringstream iss(input);

    yyFlexLexer scanner(&iss);
    std::vector<Token> out;

    while (true) {
        int r = scanner.yylex(); // только без аргументов
        out.push_back(g_tok);
        if (r == 0) break;
    }
    return out;
}
