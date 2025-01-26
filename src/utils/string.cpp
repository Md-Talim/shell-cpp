#include "string.h"

#include <string>

#define END '\0'
#define SPACE ' '
#define SINGLE '\''
#define DOUBLE '"'
#define BACKSLASH '\\'
#define GREATER_THAN '>'

std::string remove_extra_spaces(const std::string& str) {
    std::string result;
    bool space = false;
    for (char c : str) {
        if (c == ' ') {
            if (!space) {
                result += c;
                space = true;
            }
        } else {
            result += c;
            space = false;
        }
    }
    return result;
}

char map_backslash_character(char character) {
    if (character == BACKSLASH || character == DOUBLE) return character;
    return END;
}

std::string parse_single_quotes(const std::string& str) {
    std::string result;
    bool inside_quotes = false;

    int len = str.size();

    for (int i = 0; i < len; i++) {
        if (str[i] == '\'') {
            inside_quotes = !inside_quotes;
        } else if (inside_quotes) {
            result += str[i];
        } else {
            while (str[i] == ' ' && i + 1 < len && str[i + 1] == ' ') {
                i++;
            }
            result += str[i];
        }
    }

    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}

std::string parse_double_quotes(const std::string& str) {
    std::string result;
    bool inside_quotes = false;

    int len = str.size();

    for (int i = 0; i < len; i++) {
        if (str[i] == '"') {
            inside_quotes = !inside_quotes;
        } else if (inside_quotes) {
            if (str[i] == BACKSLASH) {
                char character = str[i + 1];
                if (character == END) {
                    i++;
                    continue;
                }

                char mapped = map_backslash_character(character);

                if (mapped != END)
                    character = mapped;
                else
                    result += BACKSLASH;

                result += character;
                i++;
            } else
                result += str[i];
        } else if (str[i] == BACKSLASH) {
            char character = str[i + 1];
            if (character == END) {
                i++;
                continue;
            }

            result += character;
            i++;
        } else {
            while (str[i] == ' ' && i + 1 < len && str[i + 1] == ' ') {
                i++;
            }
            result += str[i];
        }
    }

    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}

std::string parse_backslashes(const std::string& str) {
    std::string result;
    bool escape = false;

    for (char c : str) {
        if (escape) {
            result += c;
            escape = false;
        } else if (c == '\\') {
            escape = true;
        } else {
            result += c;
        }
    }

    return result;
}
