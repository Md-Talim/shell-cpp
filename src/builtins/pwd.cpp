#include <filesystem>
#include <iostream>

#include "builtins.h"

void pwd_builtin() {
    std::cout << std::filesystem::current_path() << std::endl;
}
