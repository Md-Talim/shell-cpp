#include "shell.hpp"

std::vector<std::string> split(std::string input_queue, const std::string &needle)
{
    std::vector<std::string> result;

    while (!input_queue.empty())
    {
        size_t index = input_queue.find(needle);

        std::string argument = input_queue.substr(0, index);
        result.push_back(argument);

        if (index != std::string::npos)
            index += needle.size();

        input_queue.erase(0, index);
    }

    return result;
}
