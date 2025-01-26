#include "path.h"

#include <filesystem>
#include <iostream>
#include <sstream>
#include <vector>

bool is_executable(const std::string &path) {
    auto file_path = std::filesystem::path(path);
    return std::filesystem::exists(file_path) &&
           std::filesystem::is_regular_file(file_path) &&
           ((std::filesystem::status(file_path).permissions() &
             std::filesystem::perms::owner_exec) !=
            std::filesystem::perms::none);
}

std::string get_executable_path(const std::string &command) {
    std::string parsed_command;
    std::string front_char, rear_char;
    if (command.front() == '\'' or command.front() == '"') {
        front_char = command.front();
        rear_char = command.back();
        parsed_command = command.substr(1, command.size() - 1);
    } else {
        parsed_command = command;
        front_char = "";
        rear_char = "";
    }

    std::string path = std::getenv("PATH");
    std::stringstream ss(path);
    std::string dir;

    char delimiter = ':';

#ifdef _WIN32
    delimiter = ';';  // Use semicolon on Windows
#endif

    while (std::getline(ss, dir, delimiter)) {
        std::string full_path = dir + "/" + parsed_command;
        if (is_executable(full_path)) {
            return dir + "/" + front_char + parsed_command + rear_char;
        }
    }

    return "";
}
