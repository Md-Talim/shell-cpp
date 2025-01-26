#include "command.h"

#include <cstdlib>
#include <iostream>

#include "path.h"
#include "string.h"

std::tuple<std::string, std::string> parse_command(std::string& input) {
    int space_index = input.find(' ');

    if (space_index == std::string::npos) {
        if (input[0] == '\'')
            input = parse_single_quotes(input);
        else if (input[0] == '\"')
            input = parse_double_quotes(input);

        return {input, ""};
    } else {
        std::string command = input.substr(0, space_index);
        if (input[0] == '\'')
            command = parse_single_quotes(command);
        else if (input[0] == '\"')
            command = parse_double_quotes(command);

        return {input.substr(0, space_index), input.substr(space_index + 1)};
    }
}

void execute_external(std::string& command, std::string& arguments) {
    std::string executable_path = get_executable_path(command);
    if (!executable_path.empty()) {
        std::string full_command = command + " " + arguments;
        system(full_command.c_str());
    } else {
        std::cout << command << ": command not found" << std::endl;
    }
}
