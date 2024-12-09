cmake_minimum_required(VERSION 3.13)

project(shell-starter-cpp)

# file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.hpp)

set(CMAKE_CXX_STANDARD 23) # Enable the C++23 standard

include_directories(include)
include_directories(src/utils)

add_executable(shell
src/main.cpp
src/shell.cpp
src/builtins/echo.cpp
src/builtins/exit.cpp
src/builtins/type.cpp
src/utils/path.cpp
src/utils/command.cpp
)
