#include <iostream>

#include "builtins.h"

void echo_builtin(const std::string& argument) {
    if (argument[0] == '\'') {
        std::cout << argument.substr(1, argument.size() - 2) << std::endl;
    } else {
        std::cout << argument << std::endl;
    }
}
