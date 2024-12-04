#include <iostream>
#include <unordered_map>
#include <functional>

void handle_invalid_command(std::string command) {
  std::cout << command << ": command not found" << std::endl;
}

int main() {
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

    std::unordered_map<std::string, std::function<void()>> commands = {};

  while (true) {
    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);

    auto command = commands.find(input);

    if (command != commands.end()) {
      command->second();
    } else {
      handle_invalid_command(input);
    }
  }
}
