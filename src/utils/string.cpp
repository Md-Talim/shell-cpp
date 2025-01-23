#include "string.h"

#include <string>

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

std::string parse_double_quotes(const std::string& str) {
    std::string result;
    bool inside_quotes = false;

    for (char c : str) {
        if (c == '"') {
            inside_quotes = !inside_quotes;
            if (!inside_quotes && !result.empty()) {
                result += " ";
            }
        } else if (inside_quotes) {
            result += c;
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
