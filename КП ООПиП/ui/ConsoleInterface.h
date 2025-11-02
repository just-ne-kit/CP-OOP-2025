#pragma once

#include <iostream>
#include <iomanip>
#include <windows.h>
#include "../session/UserSession.h"

using namespace std;

class ConsoleInterface
{
private:
    const unsigned int width = 156;
    const unsigned int height = 41;

    HANDLE buffers[2];
    int active = 0;

    void swapBuffers() {
        active = 1 - active;
        SetConsoleActiveScreenBuffer(buffers[active]);
    }

    void clearBuffer() {
        DWORD written;
        COORD origin = { 0, 0 };
        CONSOLE_SCREEN_BUFFER_INFO info;
        GetConsoleScreenBufferInfo(buffers[1 - active], &info);
        DWORD size = info.dwSize.X * info.dwSize.Y;

        FillConsoleOutputCharacterA(buffers[1 - active], ' ', size, origin, &written);
    }
    
    void hideCursor() {
        for (int i = 0; i < 2; i++)
        {
            CONSOLE_CURSOR_INFO cursorInfo;
            GetConsoleCursorInfo(buffers[i], &cursorInfo);
            cursorInfo.bVisible = FALSE;
            SetConsoleCursorInfo(buffers[i], &cursorInfo);
        }
    }

    void showCursor() {
        for (int i = 0; i < 2; i++)
        {
            CONSOLE_CURSOR_INFO cursorInfo;
            GetConsoleCursorInfo(buffers[i], &cursorInfo);
            cursorInfo.bVisible = TRUE;
            SetConsoleCursorInfo(buffers[i], &cursorInfo);
        }
    }

    void move_cursor(int x, int y) {
        COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
        SetConsoleCursorPosition(buffers[active], pos);
    }
public:
    ConsoleInterface() {
        buffers[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL,
            CONSOLE_TEXTMODE_BUFFER, NULL);
        buffers[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL,
            CONSOLE_TEXTMODE_BUFFER, NULL);
        SetConsoleActiveScreenBuffer(buffers[active]);
    }

    void drawLines(const std::vector<std::string>& lines) {
        clearBuffer();
        DWORD written;
        COORD pos;
        for (int i = 0; i < lines.size(); ++i) {
            pos = { 0, static_cast<SHORT>(i) };
            WriteConsoleOutputCharacterA(buffers[1 - active], lines[i].c_str(), lines[i].size(), pos, &written);
        }
        swapBuffers();
    }
    void draw_screen_1(const std::string& input) {
        int max = 19;
        int width = max - input.size();
        std::string res = width < 0 ? std::string(max, ' ') : input + std::string(width, ' ');
        drawLines({
            "+------------------------+",
            "|   Введите команду:     |",
            "|   > " + res + "|",
            "+------------------------+",
            "| [Enter] OK [Esc] Выход |"
            });
        move_cursor(6 + input.size(), 2);
    }
    //1 - Регистрация
    //2 - Вход
    void auth_0();

    //Введите новый логин: login
    //Введите новый пароль: password_1
    //Повторите пароль: password_2
    void auth_1(const std::string& login, const std::string& password_1, const std::string& password_2);
    
    //Пользователь с таким логином уже существует.
    //Нажмите любую клавишу для продолжения...
    void auth_1_error_1();
    
    //Повторный пароль введен неверно.
    //Нажмите любую клавишу для продолжения...
    void auth_1_error_2();
    
    //Логин: login
    //Пароль: password
    void auth_2(const std::string& login, const std::string& password);
    
    //Неверный логин или пароль.
    //Нажмите любую клавишу для продолжения...
    void auth_2_error_1();
};
