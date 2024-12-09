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
    std::string path = std::getenv("PATH");
    std::stringstream ss(path);
    std::string dir;

    char delimiter = ':';

#ifdef _WIN32
    delimiter = ';';  // Use semicolon on Windows
#endif

    while (std::getline(ss, dir, delimiter)) {
        auto file_path = std::filesystem::path(dir) / command;
        if (is_executable(file_path.string())) {
            return file_path.string();
        }
    }

    return "";
}
