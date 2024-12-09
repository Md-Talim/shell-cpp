#ifndef PATH_H
#define PATH_H

#include <string>

bool is_executable(const std::string& path);
std::string get_executable_path(const std::string& command);

#endif
