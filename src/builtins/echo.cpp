#include <iostream>

#include "../utils/string.h"
#include "builtins.h"

void echo_builtin(const std::string& argument) {
    if (argument[0] == '\'') {
        std::cout << argument.substr(1, argument.size() - 2) << std::endl;
    } else if (argument[0] == '"') {
        std::cout << parse_double_quotes(argument) << std::endl;
    } else {
        std::cout << parse_backslashes(remove_extra_spaces(argument))
                  << std::endl;
    }
}
