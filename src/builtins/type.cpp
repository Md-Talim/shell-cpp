#include <algorithm>
#include <iostream>
#include <vector>

#include "../utils/path.h"
#include "builtins.h"

void type_builtin(const std::string& command) {
    if (command.empty()) {
        std::cout << "type: missing argument" << std::endl;
        return;
    }

    std::vector<std::string> builtin_commands = {"echo", "exit", "type", "pwd"};
    auto search_it =
        std::find(builtin_commands.begin(), builtin_commands.end(), command);

    // if the command is a builtin command
    if (search_it != builtin_commands.end()) {
        std::cout << command << " is a shell builtin" << std::endl;
        return;
    }

    std::string executable_path = get_executable_path(command);

    if (executable_path != "") {
        std::cout << command << " is " << executable_path << std::endl;
        return;
    }

    // if the command is not found
    std::cout << command << ": not found" << std::endl;
}
