#pragma once
#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>

class ConsoleUI {
public:
    static void pause() {
        _getch();
    }

    static void clear() {
#ifdef _WIN32
        // приоритет на ANSI escape
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
            std::cout << "\033[2J\033[H";
        }
        else {
            system("cls");
        }
#else
        std::cout << "\033[2J\033[H";
#endif
    }

    static void pause_clear(const std::string& msg) {
        std::cout << msg;
        pause();
        clear();
    }

    static int scroll(const std::vector<std::string>& options,
        const std::string& choiceMarker,
        int cur = 0,
        const std::string& header = "")
    {
        int count = options.size();
        while (true) {
            std::string result = header;
            for (int i = 0; i < count; i++) {
                result += (i == cur ? choiceMarker : "") + options[i] + "\n";
            }

            clear();
            std::cout << result << std::flush;

            int res = _getch();
            if (res == 72) cur = (cur - 1 + count) % count;   // стрелка вверх
            else if (res == 80) cur = (cur + 1) % count;      // стрелка вниз
            else if (res == '\r') return cur;                 // Enter
        }
    }
};
