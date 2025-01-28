#include "shell.hpp"

#define END '\0'
#define SPACE ' '
#define SINGLE '\''
#define DOUBLE '"'
#define BACKSLASH '\\'

namespace parsing
{
    LineParser::LineParser(const std::string &line) : iterator(std::prev(line.begin())), end(line.end()), arguments()
    {
    }

    ParsedLine LineParser::parse(void)
    {
        std::optional<std::string> argument;
        while (argument = next_argument())
            arguments.push_back(argument.value());

        return ParsedLine{.arguments = arguments};
    }

    std::optional<std::string> LineParser::next_argument()
    {
        std::string builder;

        char character;
        while ((character = next()) != END)
        {
            switch (character)
            {
            case SPACE:
            {
                if (!builder.empty())
                    return (std::optional(builder));

                break;
            }
            case BACKSLASH:
            {
                backslash(builder, false);
                break;
            }
            case SINGLE:
            {
                while ((character = next()) != END and character != SINGLE)
                    builder.push_back(character);

                break;
            }
            case DOUBLE:
            {
                while ((character = next()) != END and character != DOUBLE)
                {
                    if (character == BACKSLASH)
                        backslash(builder, true);
                    else
                        builder.push_back(character);
                }
                break;
            }
            default:
                builder.push_back(character);
            }
        }

        if (!builder.empty())
            return (std::optional(builder));

        return (std::optional<std::string>());
    }

    char LineParser::map_backslash_character(char character)
    {
        if (character == BACKSLASH || character == DOUBLE)
            return (character);

        return (END);
    }

    void LineParser::backslash(std::string &builder, bool in_quote)
    {
        char character = next();

        if (character == END)
            return;

        if (in_quote)
        {
            char mapped = map_backslash_character(character);

            if (mapped != END)
                character = mapped;
            else
                builder += BACKSLASH;
        }

        builder += character;
    }

    char LineParser::next(void)
    {
        if (iterator != end)
            ++iterator;

        if (iterator == end)
            return (END);

        return (*iterator);
    }

    char LineParser::peek(void)
    {
        std::string::const_iterator next = iterator;
        if (iterator != end)
            next = std::next(iterator);

        if (next == end)
            return (END);

        return (*next);
    }
}
