#include "shell.h"

#include <iostream>

#include "builtins/builtins.h"
#include "utils/command.h"

void Shell::run() {
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    while (true) {
        std::cout << "$ ";
        std::string input;
        std::getline(std::cin, input);

        auto [command, arguments] = parse_command(input);

        if (command == "echo") {
            echo_builtin(arguments);
        } else if (command == "type") {
            type_builtin(arguments);
        } else if (command == "exit") {
            exit_builtin();
        } else if (command == "pwd") {
            pwd_builtin();
        } else {
            execute_external(command, arguments);
        }
    }
}
