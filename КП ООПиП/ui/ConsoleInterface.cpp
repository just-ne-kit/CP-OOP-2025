#include "ConsoleInterface.h"

void ConsoleInterface::auth_0() {
    drawLines({
        "1 - Регистрация",
        "2 - Вход"
        });
}
void ConsoleInterface::auth_1(const std::string& login, const std::string& password_1, const std::string& password_2) {
    drawLines({
        "Введите новый логин: " + login,
        "Введите новый пароль: " + password_1,
        "Повторите пароль: " + password_2
        });
}
void ConsoleInterface::auth_1_error_1() {
    drawLines({
        "Пользователь с таким логином уже существует.",
        "Нажмите любую клавишу для продолжения..."
        });
}
void ConsoleInterface::auth_1_error_2() {
    drawLines({
        "Повторный пароль введен неверно.",
        "Нажмите любую клавишу для продолжения..."
        });
}
void ConsoleInterface::auth_2(const std::string& login, const std::string& password) {
    drawLines({
        "Логин: " + login,
        "Пароль: " + password
        });
}
void ConsoleInterface::auth_2_error_1() {
    drawLines({
        "Неверный логин или пароль.",
        "Нажмите любую клавишу для продолжения..."
        });
}