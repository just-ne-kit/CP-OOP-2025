#include "InputReader.h"

#include <iostream>
#include <conio.h>
#include <limits>

int InputReader::read_int(const std::string& msg, const std::string& errMsg) {
    int value;
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
int InputReader::read_int(int min, int max, const std::string& msg, const std::string& errMsg) {
    int value;
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
float InputReader::read_float(const std::string& msg, const std::string& errMsg) {
    float value;
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
float InputReader::read_float(int min, int max, const std::string& msg, const std::string& errMsg) {
    float value;
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


std::string InputReader::read_str(const std::string& msg, const std::string& errMsg) {
    std::string value;
    while (true) {
        std::cout << msg;
        std::getline(std::cin, value);

        if (!value.empty()) return value;
        std::cout << errMsg << std::endl;
    }
}

std::string InputReader::read_str(std::size_t maxCount, const std::string& msg, const std::string& errMsg) {
    std::string value;
    while (true) {
        std::cout << msg;
        std::getline(std::cin, value);

        if (!value.empty() && value.size() <= maxCount) return value;
        std::cout << errMsg << std::endl;
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