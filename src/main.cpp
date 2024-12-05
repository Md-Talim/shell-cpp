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

std::vector<std::pair<std::string, std::string>> get_path_executables() {
  // get all the path values
  const char *path_env = std::getenv("PATH");
  std::string path = path_env ? path_env : "";
  std::vector<std::string> directories;
  std::vector<std::pair<std::string, std::string>> executables;

  if (path.empty()) {
    std::cout << "Path variable not set." << std::endl;
    return executables;
  }

  // split the path strings with :
  std::stringstream ss(path);
  std::string dir;
  char delimiter = ':';

#ifdef _WIN32
  delimiter = ';';  // Use semicolon on Windows
#endif

  while (std::getline(ss, dir, delimiter)) {
    directories.push_back(dir);
  }

  for (const auto &directory : directories) {
    try {
      for (const auto &entry : std::filesystem::directory_iterator(directory)) {
        if (std::filesystem::is_regular_file(entry) &&
            is_executable(entry.path())) {
          std::string name = entry.path().filename().string();

          std::string abs_path =
              std::filesystem::absolute(entry.path()).string();

          executables.push_back({name, abs_path});
        }
      }
    } catch (const std::filesystem::filesystem_error &e) {
      continue;
    }
  }

  return executables;
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

  std::vector<std::pair<std::string, std::string>> execuatables =
      get_path_executables();
  for (const auto executable : execuatables) {
    // if the command is an executable command
    if (executable.first.find(command) != std::string::npos) {
      print_executable(executable.second);
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
