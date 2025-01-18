#include <iostream>

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
    std::string result;
    bool inside_quotes = false;

    for (char c : str) {
        if (c == '"') {
            inside_quotes = !inside_quotes;
            if (!inside_quotes && !result.empty()) {
                result += " ";
            }
        } else if (inside_quotes) {
            result += c;
        }
    }

    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
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
