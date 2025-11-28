#pragma once

#include <string>

class InputReader
{
public:
    template<typename T>
    static T read(const std::string& msg = "", const std::string& errMsg = "");
    template<typename T>
    static T read(const T& min, const T& max, const std::string& msg = "", const std::string& errMsg = "");

    template<typename T>
    static T read(std::size_t maxCount, const std::string& msg = "", const std::string& errMsg = "");

    static std::string read_password(const std::string& msg = "", const std::string& errMsg = "");
    static std::string read_password(std::size_t maxCount, const std::string& msg = "", const std::string& errMsg = "");
};