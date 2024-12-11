#include "navigation.h"

#include <algorithm>
#include <filesystem>
#include <string>

Navigation::Navigation() {
    std::filesystem::path current_path = std::filesystem::current_path();
    current_directory = current_path.string();
    std::replace(current_directory.begin(), current_directory.end(), '\\', '/');
}
