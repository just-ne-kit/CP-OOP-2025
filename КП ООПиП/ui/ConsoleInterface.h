#pragma once

#include <iostream>
#include <iomanip>
#include <windows.h>
#include "../session/UserSession.h"

using namespace std;

class ConsoleInterface
{
private:
    HANDLE buffers[2];
    int active = 0;

    void swapBuffers();
    void clearBuffer();
public:
    ConsoleInterface();
    
    void hideCursor();
    void showCursor();
    void move_cursor(int x, int y);
    
    void drawLines(const std::vector<std::string>& lines);
};
