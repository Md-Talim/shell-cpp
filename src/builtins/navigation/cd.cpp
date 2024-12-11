#include <filesystem>
#include <iostream>

#include "navigation.h"

// Utility to check if a folder exists or not
bool is_exists(std::string path) {
    return std::filesystem::exists(path) && std::filesystem::is_directory(path);
}

void Navigation::cd(std::string path) {
    if (!is_exists(path)) {
        std::cout << "cd: " << path << ": No such file or directory"
                  << std::endl;
        return;
    }

    current_directory = path;
}
