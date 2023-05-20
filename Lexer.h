//
// Created by Vihaan Zinjuvadia on 5/13/23.
//

#ifndef FUNCTIONPARSER_LEXER_H
#define FUNCTIONPARSER_LEXER_H

#include <string>
#include <vector>
#include "Parser.h"


// NOT HANDLE IMPLICIT MULTIPLICATION YET, BUT WHAT I COULD DO IS INSERT A MULTIPLICATION SYMBOL
// BETWEEN LHS & OPEN PARENTHESIS AND BETWEEN NUMBER & FUNCTION AND BETWEEN NUMBER & VARIABLE
class Lexer {
private:
    // Later have 2 variables for graphing advanced functions
    std::string function;
    char variable;
    const std::vector<std::string> special_tokens;
    const std::vector<std::string> operators;
    const std::vector<std::string> constants;

    const int PIXELS_PER_UNIT;

    bool in(const std::string &c, const std::vector<std::string> &vec);
    bool isNumeric(char c);
    bool isCharacter(char c);
public:
    Lexer(const char &var, const std::string &function);
    std::vector<std::string> tokenize();
};


#endif //FUNCTIONPARSER_LEXER_H
