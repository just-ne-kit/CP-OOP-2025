#include "Parser.h"
#include <algorithm>

bool Parser::is_digit(char c) {
    return c >= '0' && c <= '9';
}

bool Parser::is_int(const std::string& s) {
    if (s.empty()) return false;
    if (s.size() > 1 && s[0] == '0') return false; // запрет ведущего нуля
    return std::all_of(s.begin(), s.end(), [](char c) { return is_digit(c); });
}

int Parser::to_int(const std::string& s) {
    if (!is_int(s)) return 0;
    return std::stoi(s);
}

bool Parser::is_float(const std::string& s) {
    if (s.empty()) return false;

    bool dotSeen = false;
    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];
        if (i == 0 && c == '-') continue;
        if (c == '.') {
            if (dotSeen || i == 0) return false; // точка не первая и только одна
            dotSeen = true;
            continue;
        }
        if (!is_digit(c)) return false;

        if (i == 1 && s[0] == '0' && c != '.') return false;
    }
    return true;
}

float Parser::to_float(const std::string& s) {
    if (!is_float(s)) return 0;
    return std::stof(s);
}

int Parser::to_phone(const std::string& s) {
    if (s.empty() || s.size() != 9 || !is_int(s)) return 0;

    return to_int(s);
}