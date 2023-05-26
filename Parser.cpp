//
// Created by Vihaan Zinjuvadia on 5/17/23.
//

#include "Parser.h"
#include <algorithm>

Parser::Parser(const std::vector<std::string> &tokens)
    : tokens {tokens}, current_index {0}, current_token {tokens.at(0)} {
}


Node* Parser::parse() {
    return this->parse_expression();
}

/*
expr     : term ((PLUS | MINUS) term)*
term     : expo ((MUL | DIV) expo)*
expo     : factor ((EXPO) factor)*
factor   : INTEGER | LPAREN expr RPAREN
*/
void Parser::advance() {
    current_index++;

    if (current_index < tokens.size()) {
        current_token = tokens.at(current_index);
    }
}

Node* Parser::parse_expression() {
    auto node = this->parse_term();
    while (current_token == "+" || current_token == "-") {
        auto left = node;
        node = new Node(current_token);
        node->left = left;
        this->advance();
        node->right = this->parse_term();
    }
    return  node;
}

Node* Parser::parse_term() {
    auto node = this->parse_exponents();
    while (current_token == "*" || current_token == "/") {
        auto left = node;
        node = new Node(current_token);
        node->left = left;
        this->advance();
        node->right = this->parse_term();
    }
    return node;
}

Node* Parser::parse_exponents() {
    auto node = this->parse_factor();
    while (current_token == "^") {
        auto left = node;
        node = new Node(current_token);
        node->left = left;
        this->advance();
        node->right = this->parse_factor();
    }
    return node;
}

Node* Parser::parse_factor() {
    std::string previous_token {};
    Node *node = nullptr;
                                                 // Hard coding in the variable, change later;
    if (std::isdigit(current_token.at(0)) || current_token == "x") {
        previous_token = current_token;
        node = new Node(current_token);
        this->advance();
        return node;
    } else if (current_token == "(") {
        this->advance();
        auto temp = this->parse_expression();
        node = new Node(current_token);
        node = temp;
        this->advance();
        return node;
    }
    return node;
}