#include "InputReader.h"

#include <iostream>
#include <conio.h>
#include <limits>

template<typename T>
T InputReader::read(const std::string& msg, const std::string& errMsg)
{
    T value;
    std::cin.unsetf(std::ios::skipws);
    while (true) {
        std::cout << msg;
        std::cin >> value;

        if (!std::cin.fail()) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.setf(std::ios::skipws);
            return value;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << errMsg;
    }
}

template<>
std::string InputReader::read<std::string>(const std::string& msg, const std::string& errMsg)
{
    std::string value;
    while (true) {
        std::cout << msg;
        std::getline(std::cin, value);

        if (!value.empty()) return value;
        std::cout << errMsg << std::endl;
    }
}

template<typename T>
T InputReader::read(const T& min, const T& max, const std::string& msg, const std::string& errMsg)
{
    T value;
    std::cin.unsetf(std::ios::skipws);
    while (true) {
        std::cout << msg;
        std::cin >> value;

        if (!std::cin.fail() && value >= min && value <= max) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.setf(std::ios::skipws);
            return value;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << errMsg;
    }
}

template int InputReader::read<int>(const std::string&, const std::string&);
template unsigned int InputReader::read<unsigned int>(const std::string&, const std::string&);
template float InputReader::read<float>(const std::string&, const std::string&);

template int InputReader::read<int>(const int&, const int&, const std::string&, const std::string&);
template unsigned int InputReader::read<unsigned int>(const unsigned int&, const unsigned int&, const std::string&, const std::string&);
template float InputReader::read<float>(const float&, const float&, const std::string&, const std::string&);

template<typename T>
T InputReader::read(std::size_t maxCount, const std::string& msg, const std::string& errMsg)
{
    return T{};
}

template<>
std::string InputReader::read<std::string>(std::size_t maxCount, const std::string& msg, const std::string& errMsg) {
    std::string value;
    while (true) {
        if (!msg.empty()) std::cout << msg;
        std::getline(std::cin, value);

        if (value.empty() || value.size() > maxCount) {
            if (!errMsg.empty()) {
                std::cout << errMsg;
            }
            continue;
        }
        return value;
    }
}

std::string InputReader::read_password(const std::string& msg, const std::string& errMsg)
{
    std::string password;
    char ch;

    std::cout << msg;
    while ((ch = _getch()) != '\r') { 
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b"; 
            }
        }
        else {
            password.push_back(ch);
            std::cout << '*';
        }
    }
    std::cout << std::endl;
    return password;
}

std::string InputReader::read_password(std::size_t maxCount, const std::string& msg, const std::string& errMsg)
{
    std::string password;
    char ch;

    std::cout << msg;
    while ((ch = _getch()) != '\r') { 
        if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b"; 
            }
        }
        else {
            if (password.size() < maxCount) {
                password.push_back(ch);
                std::cout << '*';
            }
        }
    }
    std::cout << std::endl;

    if (password.empty()) {
        std::cout << errMsg << std::endl;
    }

    return password;
}