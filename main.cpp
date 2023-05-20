#include "Lexer.h"
#include "Parser.h"
#include <iostream>
#include <iomanip>

const std::vector<std::string> operators {"+", "-", "*", "/", "^", "(", ")"};

void printTreeInorder(const Node *n) {
    if (n->left != nullptr) {
        printTreeInorder(n->left);
    }

    std::cout << n->value << "\n";

    if (n->right != nullptr) {
        printTreeInorder(n->right);
    }
}

double operator_evaluate(const std::string &v1, const std::string &v2, const std::string &operand) {
    double sum = 0;
    auto num1 = std::stof(v1);
    auto num2 = std::stof(v2);

    if (operand == "+") {
        sum += (num1 + num2);
    } else if (operand == "-") {
        sum += (num1 - num2);
    } else if (operand == "*") {
        sum += (num1 * num2);
    } else if (operand == "/") {
        sum += (num1/num2);
    } else if (operand == "^") {
        sum += pow(num1, num2);
    }

    return sum;
}

void evaluate(Node *n) {
    if (n->left) {
        evaluate(n->left);
    }
    if (n->right) {
        evaluate(n->right);
    }
    if ( n->left && n->right && (std::isdigit(n->left->value.at(0)) && std::isdigit(n->right->value.at(0))) ) {
        auto value = operator_evaluate(n->left->value, n->right->value, n->value);
        n->value = std::to_string(value);
        n->left = nullptr;
        n->right = nullptr;
    }
    return;
}

int main() {
    const char variable {'x'};
    Lexer lexer = Lexer(variable, "5*15"); // Doesn't work with exponent, can only print 3 things of the tree, etc.
    auto tokens = lexer.tokenize();

    Parser parser = Parser(tokens);
    auto tree = parser.parse();

    evaluate(tree);
    std::cout << "Evaluation: " << tree->value << std::endl;

    // For Parser, before parsing the expression, replace 'x' with the value to parse at
    // Include later about how to do handle decimals, and correct number of parentheses

    return 0;
}
