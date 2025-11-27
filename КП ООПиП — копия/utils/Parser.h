#pragma once

#include <string>

class Parser {
public:
    static bool is_digit(char c);
    
    static bool is_int(const std::string& s);
    static int to_int(const std::string& s);

    static bool is_float(const std::string& s);
    static float to_float(const std::string& s);

    static int to_phone(const std::string& s);
};
