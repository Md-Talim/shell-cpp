#ifndef BUILTINS_H
#define BUILTINS_H

#include <string>

void echo_builtin(const std::string& argument);
void type_builtin(const std::string& command);
void exit_builtin();

#endif
