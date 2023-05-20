//
// Created by Vihaan Zinjuvadia on 5/13/23.
//

#include "Lexer.h"
#include <iostream>

Lexer::Lexer(const char &var, const std::string &function)
    : variable {var}, function {function}, PIXELS_PER_UNIT {10}, constants {"pi", "e"},
      operators {"+", "-", "*", "/", "^", "(", ")"},
      special_tokens {
            "sin", "cos", "tan", "csc", "sec", "cot", "arcsin", "arccos", "arctan",
            "arccsc", "arcsec", "arccot", "sinh", "cosh", "tanh", "csch", "sech",
            "coth", "arcsinh", "arccosh", "arctanh", "arccsch", "arcsech", "arccoth",
            "sqrt","cbrt", "log", "ln"
      }
    {}

bool Lexer::in(const std::string &c, const std::vector<std::string> &vec) {
    return std::any_of(vec.begin(), vec.end(),
                       [&c] (const std::string& s) {return s==c;});
}

bool Lexer::isNumeric(char c) {
    return (int(c) >= 48 && int(c) <= 57);
}
bool Lexer::isCharacter(char c) {
    return (int(c) >= 97 && int(c) <= 122);
}

// just basic tokenizer rn, worry about functions later.
std::vector<std::string> Lexer::tokenize() {
    std::vector<std::string> tokens {};
    for (int i {}; i < function.length(); i++) {
        char at {function.at(i)};

        // Ignoring Whitespace And Other Characters
        if (at == ' ' || at == '\n' || at == '\t') {

        }
        // Handling Operators
          else if (at == '+') {
            tokens.push_back(std::string(1, at));
        } else if (at == '-') {
            tokens.push_back(std::string(1, at));
        } else if (at == '*') {
            tokens.push_back(std::string(1, at));
        } else if (at == '/') {
            tokens.push_back(std::string(1, at));
        } else if (at == '^') {
            tokens.push_back(std::string(1, at));
        } else if (at == '(') {
            tokens.push_back(std::string(1, at));
        } else if (at == ')') {
            tokens.push_back(std::string(1, at));
        }
        // Handling Variable
        else if (at == variable) {
            tokens.push_back(std::string(1, at));
        }

        // Handling Numbers, Constants and Later, Functions
        else {
            // Handling Number
            std::string number {};
            std::string special_token {};

            if (isNumeric(at)) {
                while (isNumeric(at)) {
                    number.push_back(at);
                    i++;
                    at = function[i];

                }
                tokens.push_back(number);
                // To make sure that i++ doesn't happen twice and that we skip over a token;
                i--;
            }

            // Handling Function (LATER)
            else if (isCharacter(at)) {
                while (isCharacter(at)) {
                    special_token.push_back(at);
                    i++;
                    at = function[i];
                }
                // To make sure that i++ doesn't happen twice and that we skip over a token;
                i--;

                if (in(special_token, special_tokens) || in(special_token, constants)) {
                    tokens.push_back(special_token);
                } else {
                    std::cout << "INVALID TOKEN!: " << special_token << std::endl;
                    std::exit(1);
                }
            }
            else {
                std::cout << "INVALID TOKEN!: " << at << std::endl;
            }
        }
    }

    return tokens;
}