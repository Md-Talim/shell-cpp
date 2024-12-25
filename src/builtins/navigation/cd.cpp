#include <filesystem>
#include <iostream>

#include "navigation.h"

// Utility to check if a folder exists or not
bool is_exists(std::string path) {
    return std::filesystem::exists(path) && std::filesystem::is_directory(path);
}

void Navigation::cd(std::string path) {
    std::filesystem::path new_path = path;

    // Handle relative paths
    if (new_path.is_relative()) {
        new_path = std::filesystem::current_path() / new_path;
    }

    if (!is_exists(new_path.string())) {
        std::cout << "cd: " << path << ": No such file or directory"
                  << std::endl;
        return;
    }

    std::filesystem::current_path(new_path);
    current_directory = new_path.string();
}
