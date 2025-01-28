#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>

#include <iostream>

#include "shell.hpp"

void prompt()
{
    std::cout << "$ ";
}

void exec(const std::string &path, const std::vector<std::string> &arguments)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        size_t size = arguments.size();

        char *argv[size + 1];
        argv[size] = NULL;

        for (size_t index = 0; index < size; ++index)
            argv[index] = const_cast<char *>(arguments[index].c_str());

        execvp(path.c_str(), argv);
        perror("execvp");
        exit(1);
    }
    else
        waitpid(pid, NULL, 0);
}

void eval(std::string &line)
{
    auto parsed_line = parsing::LineParser(line).parse();

    std::vector<std::string> &arguments = parsed_line.arguments;
    std::string program = arguments[0];

    builtins::registry_map::iterator builtin = builtins::REGISTRY.find(program);

    if (builtin != builtins::REGISTRY.end())
    {
        builtin->second(arguments);
        return;
    }

    std::string path;

    if (locate(program, path))
    {
        exec(path, arguments);
        return;
    }

    std::cout << program << ": command not found" << std::endl;
}

struct termios_prompt
{
    struct termios previous;

    termios_prompt()
    {
        tcgetattr(STDIN_FILENO, &previous);

        struct termios new_ = previous;
        new_.c_lflag &= ~(ECHO | ICANON);
        new_.c_cc[VMIN] = 1;
        new_.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &new_);
    }

    ~termios_prompt() { tcsetattr(STDIN_FILENO, TCSANOW, &previous); }
};

enum class ReadResult
{
    QUIT,
    EMPTY,
    CONTENT,
};

ReadResult read(std::string &line)
{
    line.clear();

    prompt();
    termios_prompt _;
    bool bell_rang = false;

    while (true)
    {
        char character = getchar();

        if (character == 0x4)
        {
            if (line.empty())
                return (ReadResult::QUIT);
        }
        else if (character == '\n')
        {
            std::cout << std::endl;
            return (line.empty() ? ReadResult::EMPTY : ReadResult::CONTENT);
        }
        else if (character == 0x1b)
        {
            getchar(); // '['
            getchar(); // 'A' or 'B' or 'C' or 'D'
        }
        else if (character == 0x7f)
        {
            if (line.empty())
                continue;

            std::cout << "\b \b" << std::flush;
            line.pop_back();
        }
        else
        {
            std::cout << character << std::flush;
            line.push_back(character);
        }
    }
}

int main()
{
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    builtins::register_defaults();

    std::string input;
    while (true)
    {
        switch (read(input))
        {
        case ReadResult::QUIT:
            return 0;
        case ReadResult::EMPTY:
            continue;
        case ReadResult::CONTENT:
            eval(input);
        }
    }
}
