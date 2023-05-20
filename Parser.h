//
// Created by Vihaan Zinjuvadia on 5/17/23.
//

#ifndef FUNCTIONPARSER_PARSER_H
#define FUNCTIONPARSER_PARSER_H


#include <vector>
#include <string>
#include "Node.h"

class Parser {
    /*
    expr     : term ((PLUS | MINUS) term)*
    term     : expo ((MUL | DIV) expo)*
    expo     : factor ((EXPO) factor)*
    factor   : INTEGER | LPAREN expr RPAREN
    */
private:
    const std::vector<std::string> &tokens;
    std::string current_token;
    int current_index;

    void advance();
public:
    Parser(const std::vector<std::string> &tokens);
    Node* parse(); /// THIS WHOLE THING RETURNS THE WHOLE AST OF THE EQUATION
    Node* parse_expression(); // Lowest Precedence, first called -->  expr: term ((PLUS | MINUS) term)*
    Node* parse_term();       // Expressions could have terms which are multiplied or divided -->  term: expo ((MUL | DIV) expo)*
    Node* parse_exponents();  // Terms could have exponents
    Node* parse_factor();     // Exponents have integers or parenthesis
};


#endif //FUNCTIONPARSER_PARSER_H
