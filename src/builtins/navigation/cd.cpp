#include <filesystem>
#include <iostream>

#include "navigation.h"

std::string get_home_directory() {
#ifndef _WIN32
    return std::getenv("HOME");
#else
    return std::getenv("USERPROFILE");
#endif
}

// Utility to check if a folder exists or not
bool is_exists(std::string path) {
    return std::filesystem::exists(path) && std::filesystem::is_directory(path);
}

void Navigation::cd(std::string path) {
    std::filesystem::path new_path = path;

    if (path == "~") {
        new_path = get_home_directory();
    } else if (path.rfind("~/", 0) == 0) {
        new_path = get_home_directory() + path.substr(1);
    }

    // Handle relative paths
    if (new_path.is_relative()) {
        new_path = std::filesystem::current_path() / new_path;
    }

    if (!is_exists(new_path.string())) {
        std::cout << "cd: " << path << ": No such file or directory"
                  << std::endl;
        return;
    }

    new_path = std::filesystem::canonical(new_path);

    std::filesystem::current_path(new_path);
    current_directory = new_path.string();
}
