#ifndef STRING_H
#define STRING_H

#include <string>

std::string remove_extra_spaces(const std::string& str);
std::string parse_double_quotes(const std::string& str);
std::string parse_backslashes(const std::string& str);

#endif  // STRING_H
