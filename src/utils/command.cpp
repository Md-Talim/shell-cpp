#include "command.h"

#include <cstdlib>
#include <iostream>

#include "path.h"
#include "string.h"

std::tuple<std::string, std::string> parse_command(std::string& input) {
    int i = 1;
    if (input.front() == '\'' || input.front() == '"') {
        char quote = input.front();
        while (i < input.size() and input[i] != quote) i++;
    }
    int space_index = input.find(' ', i);

    if (space_index == std::string::npos) {
        return {input, ""};
    } else {
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
