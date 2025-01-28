#ifndef SHELL_H
#define SHELL_H

#include <functional>
#include <map>
#include <optional>
#include <string>
#include <vector>

void prompt();

std::vector<std::string> split(std::string haystack, const std::string &needle);
bool locate(const std::string &program, std::string &output);

namespace builtins
{
    using registry_map = std::map<std::string, std::function<void(const std::vector<std::string> &)>>;
    extern registry_map REGISTRY;

    void register_defaults();
} // namespace builtins

namespace parsing
{
    typedef struct
    {
        std::vector<std::string> arguments;
    } ParsedLine;

    class LineParser
    {
    private:
        std::string::const_iterator iterator;
        std::string::const_iterator end;
        std::vector<std::string> arguments;

    public:
        LineParser(const std::string &line);

    public:
        ParsedLine parse(void);

    private:
        std::optional<std::string> next_argument();
        void backslash(std::string &builder, bool in_quote);
        char map_backslash_character(char character);
        char next(void);
        char peek(void);
    };
}; // namespace parsing

#endif // SHELL_H
