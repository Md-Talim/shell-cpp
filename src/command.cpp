#include <fcntl.h>
#include <unistd.h>

#include <climits>
#include <cstring>
#include <iostream>

#include "shell.hpp"

bool locate(const std::string &program, std::string &output)
{
    if (program[0] == '/')
    {
        if (access(program.c_str(), F_OK | X_OK) == 0)
        {
            output = program;
            return true;
        }

        return false;
    }

    const char *$path = getenv("PATH");
    if (!$path)
        return false;

    std::vector<std::string> paths = split(std::string($path), ":");

    for (std::vector<std::string>::iterator iterator = paths.begin(); iterator != paths.end(); ++iterator)
    {
        std::string path = *iterator + "/" + program;

        if (access(path.c_str(), F_OK | X_OK) == 0)
        {
            output = path;
            return true;
        }
    }

    return false;
}

namespace builtins
{
    registry_map REGISTRY;

    void exit(const std::vector<std::string> &_)
    {
        std::exit(0);
    }

    void echo(const std::vector<std::string> &arguments)
    {
        size_t size = arguments.size();
        size_t last_index = size - 1;

        for (size_t index = 1; index < size; ++index)
        {
            std::cout << arguments[index];

            if (index != last_index)
                std::cout << " ";
        }

        std::cout << std::endl;
    }

    void type(const std::vector<std::string> &arguments)
    {
        std::string program = arguments[1];

        builtins::registry_map::iterator builtin = builtins::REGISTRY.find(program);
        if (builtin != builtins::REGISTRY.end())
        {
            printf("%s is a shell builtin\n", program.c_str());
            return;
        }

        std::string path;
        if (locate(program, path))
        {
            printf("%s is %s\n", program.c_str(), path.c_str());
            return;
        }

        printf("%s: not found\n", program.c_str());
    }

    void pwd(const std::vector<std::string> &_)
    {
        char path[PATH_MAX] = {};
        getcwd(path, sizeof(path));
        printf("%s\n", path);
    }

    void cd(const std::vector<std::string> &arguments)
    {
        std::string absolute_path;

        const std::string &path = arguments[1];

        if (path[0] == '/')
            absolute_path = path;
        else if (path[0] == '.')
        {
            char current_path[PATH_MAX] = {};
            getcwd(current_path, sizeof(current_path));
            absolute_path = std::string(current_path) + "/" + path;
        }
        else if (path[0] == '~')
        {
            const char *$home = getenv("HOME");
            if (!$home)
                printf("cd: HOME not set\n");
            else
                absolute_path = std::string($home) + "/" + path.substr(1);
        }

        if (absolute_path.empty())
            return;
        if (chdir(absolute_path.c_str()) == -1)
            printf("cd: %s: No such file or directory\n", path.c_str());
    }

    void register_defaults()
    {
        REGISTRY.insert({"exit", exit});
        REGISTRY.insert({"echo", echo});
        REGISTRY.insert({"type", type});
        REGISTRY.insert({"pwd", pwd});
        REGISTRY.insert({"cd", cd});
    }
} // namespace builtins
