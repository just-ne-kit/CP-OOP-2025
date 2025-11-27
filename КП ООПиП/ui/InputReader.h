#pragma once

#include <string>

class InputReader
{
public:
    static int read_int(int min, int max, const std::string& msg = "", const std::string& errMsg = "");
    static int read_int(const std::string& msg = "", const std::string& errMsg = "");

    static float read_float(int min, int max, const std::string& msg = "", const std::string& errMsg = "");
    static float read_float(const std::string& msg = "", const std::string& errMsg = "");

    static std::string read_str(std::size_t maxCount, const std::string& msg = "", const std::string& errMsg = "");
    static std::string read_str(const std::string& msg = "", const std::string& errMsg = "");

    static std::string read_password(const std::string& msg = "", const std::string& errMsg = "");
    static std::string read_password(std::size_t maxCount, const std::string& msg = "", const std::string& errMsg = "");
};