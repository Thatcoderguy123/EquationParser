#include "Lexer.h"
#include "Parser.h"
#include <iostream>

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
    double num1 = std::stod(v1);
    double num2 = std::stod(v2);

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

void evaluate(Node *n, const double replace) {
    // hardcoding in variable, change later
    if (n->value == "x") {
        n->value = std::to_string(replace);
    }

    if (n->left) {
        evaluate(n->left, replace);
    }
    if (n->right) {
        evaluate(n->right, replace);
    }

    if (n->left && n->right && (std::isdigit(n->left->value.at(0)) && std::isdigit(n->right->value.at(0))) ) {
        auto value = operator_evaluate(n->left->value, n->right->value, n->value);
        n->value = std::to_string(value);
        n->left = nullptr;
        n->right = nullptr;
    }
    return;
}

int main() {
    const char variable {'x'};
    Lexer lexer = Lexer(variable, "2(xx)");
    auto tokens = lexer.tokenize();

    Parser parser = Parser(tokens);
    auto tree = parser.parse();

    evaluate(tree, 2); // giving wrong value why?
    std::cout << "Evaluation: " << tree->value << std::endl;

    return 0;
}
