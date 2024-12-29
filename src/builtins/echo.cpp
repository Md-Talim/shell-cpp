#include <iostream>
#include <stack>

#include "builtins.h"

std::string remove_extra_spaces(const std::string& str) {
    std::string result;
    bool space = false;
    for (char c : str) {
        if (c == ' ') {
            if (!space) {
                result += c;
                space = true;
            }
        } else {
            result += c;
            space = false;
        }
    }
    return result;
}

std::string parse_double_quotes(const std::string& str) {
    std::stack<char> st;
    std::string result;

    for (char c : str) {
        if (c != '"') {
            result += c;
        }
    }

    return result;
}

void echo_builtin(const std::string& argument) {
    if (argument[0] == '\'') {
        std::cout << argument.substr(1, argument.size() - 2) << std::endl;
    } else if (argument[0] == '"') {
        std::cout << parse_double_quotes(argument) << std::endl;
    } else {
        std::cout << remove_extra_spaces(argument) << std::endl;
    }
}
