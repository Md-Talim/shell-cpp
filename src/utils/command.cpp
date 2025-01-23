#include "command.h"

#include <cstdlib>
#include <iostream>

#include "path.h"

std::tuple<std::string, std::string> parse_command(std::string& input) {
    int space_index = input.find(' ');

    if (space_index == std::string::npos) {
        return {input, ""};
    } else {
        return {input.substr(0, space_index), input.substr(space_index + 1)};
    }
}

void execute_external(std::string& command, std::string& arguments) {
    bool is_executable = is_command_executable(command);
    if (is_executable) {
        std::string full_command = command + " " + arguments;
        system(full_command.c_str());
    } else {
        std::cout << command << ": command not found" << std::endl;
    }
}
