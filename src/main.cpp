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
  return access(file_path.string().c_str(), X_OK) == 0;
}

void type_builtin(std::string command) {
  if (command.empty()) {
    std::cout << "type: missing argument" << std::endl;
    return;
  }

  auto print_builtin = [command]() {
    std::cout << command << " is a shell builtin" << std::endl;
  };

  auto print_executable = [command](std::string abs_path) {
    std::cout << command << " is " << abs_path << std::endl;
  };

  auto print_not_found = [command]() {
    std::cout << command << ": not found" << std::endl;
  };

  std::vector<std::string> builtin_commands = {"echo", "exit", "type"};
  auto search_it =
      std::find(builtin_commands.begin(), builtin_commands.end(), command);

  // if the command is a builtin command
  if (search_it != builtin_commands.end()) {
    print_builtin();
    return;
  }

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

    if (std::filesystem::exists(file_path) &&
        std::filesystem::is_regular_file(file_path) &&
        ((std::filesystem::status(file_path).permissions() &
          std::filesystem::perms::owner_exec) !=
         std::filesystem::perms::none)) {
      // if the command is an executable command
      print_executable(file_path.string());
      return;
    }
  }

  // if the command is not found
  print_not_found();
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
      handle_invalid_command(input);
    }
  }
}
