#include <unistd.h>

#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void handle_invalid_command(std::string command) {
  std::cout << command << ": command not found" << std::endl;
}

void exit_builtin() { exit(0); }

void echo_builtin(std::string argument) { std::cout << argument << std::endl; }

bool is_executable(const std::filesystem::path &file_path) {
  return std::filesystem::exists(file_path) &&
         std::filesystem::is_regular_file(file_path) &&
         ((std::filesystem::status(file_path).permissions() &
           std::filesystem::perms::owner_exec) != std::filesystem::perms::none);
}

std::string get_executable_path(std::string command) {
  std::string path = std::getenv("PATH");
  std::vector<std::string> directories;
  std::stringstream ss(path);
  std::string dir;

  char delimiter = ':';

#ifdef _WIN32
  delimiter = ';';  // Use semicolon on Windows
#endif

  while (std::getline(ss, dir, delimiter)) {
    directories.push_back(dir);
  }

  for (const auto &dir : directories) {
    std::filesystem::path file_path = std::filesystem::path(dir) / command;

    if (is_executable(file_path)) {
      return file_path.string();
    }
  }

  return "";
}

void type_builtin(std::string command) {
  if (command.empty()) {
    std::cout << "type: missing argument" << std::endl;
    return;
  }

  std::vector<std::string> builtin_commands = {"echo", "exit", "type"};
  auto search_it =
      std::find(builtin_commands.begin(), builtin_commands.end(), command);

  // if the command is a builtin command
  if (search_it != builtin_commands.end()) {
    std::cout << command << " is a shell builtin" << std::endl;
    return;
  }

  std::string executable_path = get_executable_path(command);

  if (executable_path != "") {
    std::cout << command << " is " << executable_path << std::endl;
    return;
  }

  // if the command is not found
  std::cout << command << ": not found" << std::endl;
}

int main() {
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while (true) {
    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);

    int space_index = input.find(' ');
    std::string command;
    std::string arguments;

    if (space_index == std::string::npos) {
      command = input;
      arguments = "";
    } else {
      command = input.substr(0, space_index);
      arguments = input.substr(space_index + 1);
    }

    if (command == "echo") {
      echo_builtin(arguments);
    } else if (command == "type") {
      type_builtin(arguments);
    } else if (command == "exit") {
      exit_builtin();
    } else {
      std::string executable_path = get_executable_path(command);

      if (executable_path != "") {
        std::string full_command = executable_path + " " + arguments;
        const char *command_ptr = full_command.c_str();
        system(command_ptr);
      } else {
        handle_invalid_command(input);
      }
    }
  }
}
