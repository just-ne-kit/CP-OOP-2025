#pragma once

#include <iostream>
#include <conio.h>
#include <string>
#include <limits>

class InputReader
{
public:
    std::string ReadString(const std::string& prompt) const {
        std::cout << prompt;
        std::string input;
        std::getline(std::cin >> std::ws, input);
        return input;
    }
    int ReadInt(const std::string& prompt, const std::string& errmsg) const {
        std::cout << prompt;
        int value;
        while (!(std::cin >> value)) {
            std::cin.clear(); // сброс флага ошибки
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка ввода
            //std::cout << "Некорректный ввод. Попробуйте снова: ";
            std::cout << errmsg << std::endl;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка после числа
        return value;
    }
    std::string ReadPassword(const std::string& prompt) {
        std::cout << prompt;
        std::string password;
        char ch;
        while ((ch = _getch()) != '\r') { // Enter
            if (ch == '\b' && !password.empty()) {
                password.pop_back();
                std::cout << "\b \b";
            }
            else if (ch != '\b') {
                password += ch;
                std::cout << '*';
            }
        }
        std::cout << std::endl;
        return password;
    }
    bool Confirm(const std::string& prompt) {
        std::string answer;
        std::cout << prompt << " (y/n): ";
        std::getline(std::cin >> std::ws, answer);
        return answer == "y" || answer == "Y";
    }
};