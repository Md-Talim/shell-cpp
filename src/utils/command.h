#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <tuple>

std::tuple<std::string, std::string> parse_command(std::string& input);
void execute_external(std::string& command, std::string& arguments);

#endif
