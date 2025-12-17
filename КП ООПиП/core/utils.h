#pragma once

#include <sstream>
#include <iomanip>

namespace utils {
    inline std::string float_to_str(float price) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(2) << price;
        return oss.str();
    }
    inline std::string shorten(const std::string& s, size_t width) {
        if (s.size() <= width) return s;
        if (width <= 3) return std::string(width, '.');
        return s.substr(0, width - 3) + "...";
    }
}