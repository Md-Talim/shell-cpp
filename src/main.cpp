#include <iostream>
#include <unordered_map>
#include <functional>
#include <vector>
#include <algorithm>

void handle_invalid_command(std::string command) {
  std::cout << command << ": command not found" << std::endl;
}

void exit_builtin() {
  exit(0);
}

void echo_builtin(std::string argument) {
  std::cout << argument << std::endl;
}

void type_builtin(std::string command) {
  std::vector<std::string> builtin_commands = { "echo", "exit", "type" };
  auto search_it = std::find(builtin_commands.begin(), builtin_commands.end(), command);

  if (search_it != builtin_commands.end()) {
    std::cout << command << " is a shell builtin" << std::endl;
  } else {
    std::cout << command << ": not found" << std::endl;
  }
}

int main() {
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  while (true) {
    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);

    int space_index = input.find(' ');
    std::string command = input.substr(0, space_index);
    std::string arguments = input.substr(space_index + 1);

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
