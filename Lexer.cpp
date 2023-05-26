//
// Created by Vihaan Zinjuvadia on 5/13/23.
//

#include "Lexer.h"
#include <iostream>

#define PI 3.1415926
#define E  2.7182818

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
            std::string number {};
            std::string special_token {};

            // Handling Number
            int decimal_point_count {};
            if (isNumeric(at) || at == '.') {
                if (isNumeric(at)) {
                    while (isNumeric(at)) {
                        number += at;
                        i++;
                        at = function[i];
                        // decimal point check
                        if (at == '.') {
                            decimal_point_count++;
                            if (decimal_point_count == 1) {
                                number += at;
                                i++;
                                at = function[i];
                            }
                        }
                    }

                    tokens.push_back(number);
                    // To make sure that i++ doesn't happen twice and that we skip over a token;
                    i--;
                }
            }

            // Handling Function
            else if (isCharacter(at)) {
                while (isCharacter(at)) {
                    special_token.push_back(at);
                    i++;
                    at = function[i];
                }
                // To make sure that i++ doesn't happen twice and that we skip over a token;
                i--;

                // Function part
                if (in(special_token, special_tokens)) {
                    tokens.push_back(special_token);
                } // Constants Part
                  else if (in(special_token, constants)) {
                    if (special_token == "pi") {
                        special_token = std::to_string(PI);
                        tokens.push_back(special_token);
                    } else {
                        special_token = std::to_string(E);
                        tokens.push_back(special_token);
                    }
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

    // Handling Implicit Multiplication
    for (int i {}; i < tokens.size()-1;i++) {
        auto at = tokens.at(i);
        auto next = tokens.at(i+1);
        // CASE: NUMBER (<VARIABLE || NUMBER, FUNCTION>)
        if (isNumeric(at.at(0)) && next == "(") {
            tokens.insert(tokens.begin() + i + 1, "*");
        }
        // CASE: NUMBER <VARIABLE || FUNCTION>
        else if (isNumeric(at.at(0)) && ((next.size() == 1 && next.at(0) == variable)) || in(next, special_tokens)) {
            tokens.insert(tokens.begin() + i + 1, "*");
        }

        // CASE: Variable Variable
        else if (((at.size() == 1 && at.at(0) == variable)) && ((next.size() == 1 && next.at(0) == variable))) {
            tokens.insert(tokens.begin() + i + 1, "*");
        }
        // CASE: Variable (<VARIABLE || FUNCTION>)
        else if (((at.size() == 1 && at.at(0) == variable)) && next == "(") {
            tokens.insert(tokens.begin() + i + 1, "*");
        }
        // CASE: VARIABLE FUNCTION
        else if (((at.size() == 1 && at.at(0) == variable)) && in(next, special_tokens)) {
            tokens.insert(tokens.begin() + i + 1, "*");
        }
    }

    return tokens;
}