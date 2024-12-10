#include <algorithm>
#include <filesystem>
#include <iostream>

#include "builtins.h"

void pwd_builtin() {
    std::filesystem::path current_path = std::filesystem::current_path();
    std::string current_path_str = current_path.string();

    std::replace(current_path_str.begin(), current_path_str.end(), '\\', '/');

    std::cout << current_path_str << std::endl;
}
