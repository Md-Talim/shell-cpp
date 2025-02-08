# My Own Shell in C++

[![progress-banner](https://backend.codecrafters.io/progress/shell/2487ac07-6422-4974-b2aa-f78a1039e2f8)](https://app.codecrafters.io/users/codecrafters-bot?r=2qF)

This repository contains the code for a POSIX-compliant shell written in C++. This project is part of the ["Build Your Own Shell"](https://app.codecrafters.io/courses/shell/overview) Challenge on CodeCrafters.


## Overview

This shell can interpret shell commands, run external programs, and handle built-in commands like `cd`, `pwd`, `echo`, and more. It includes features such as command parsing, REPL (Read-Eval-Print Loop), and built-in commands. Future updates will include support for output redirection and autocompletion.

## Project Structure


- **`.codecrafters/`**: Contains scripts for compiling and running your program on CodeCrafters.
- **`.vscode/`**: Contains Visual Studio Code settings.
- **`build/`**: Directory where the build files are generated.
- **`include/`**: Contains header files.
- **`src/`**: Contains the source code for the shell and its utilities.
- **`CMakeLists.txt`**: CMake configuration file.
- **`codecrafters.yml`**: Configuration file for CodeCrafters.
- **`your_program.sh`**: Script to run your program locally.

## Getting Started

### Prerequisites

- Ensure you have `cmake` installed locally.
- Ensure you have `vcpkg` installed and configured.

### Building the Project

To build the project, run the following command:

```sh
./your_program.sh
```

This script will compile the project using CMake and build the executable.

### Running the Shell

To run the shell, execute the following command:

```sh
./build/shell
```

This will start the shell, and you can begin entering commands.

## Built-in Commands

The shell supports the following built-in commands:

| Command          | Description                                |
|------------------|--------------------------------------------|
| `cd <directory>` | Change the current directory.              |
| `pwd`            | Print the current working directory.       |
| `echo <text>`    | Print the text to the standard output.     |
| `type <command>` | Display information about the command.     |
| `exit`           | Exit the shell.                            |

## External Commands

The shell can also execute external commands found in the system's `PATH`.

## Acknowledgements

This project is part of the CodeCrafters "Build Your Own Shell" Challenge. Special thanks to the CodeCrafters team for providing the challenge and resources.
