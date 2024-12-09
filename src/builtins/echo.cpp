#include <iostream>

#include "builtins.h"

void echo_builtin(const std::string& argument) {
    std::cout << argument << std::endl;
}
