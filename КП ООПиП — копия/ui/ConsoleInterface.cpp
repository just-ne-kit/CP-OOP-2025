#include "ConsoleInterface.h"

ConsoleInterface::ConsoleInterface() {
    buffers[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL,
        CONSOLE_TEXTMODE_BUFFER, NULL);
    buffers[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL,
        CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(buffers[active]);
}

void ConsoleInterface::clearBuffer() {
    DWORD written;
    COORD origin = { 0, 0 };
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(buffers[1 - active], &info);
    DWORD size = info.dwSize.X * info.dwSize.Y;

    FillConsoleOutputCharacterA(buffers[1 - active], ' ', size, origin, &written);
}
void ConsoleInterface::drawLines(const std::vector<std::string>& lines) {
    clearBuffer();
    DWORD written;
    COORD pos;
    for (int i = 0; i < lines.size(); ++i) {
        pos = { 0, static_cast<SHORT>(i) };
        WriteConsoleOutputCharacterA(buffers[1 - active], lines[i].c_str(), lines[i].size(), pos, &written);
    }
    swapBuffers();
}
void ConsoleInterface::hideCursor(){
        for (int i = 0; i < 2; i++)
        {
            CONSOLE_CURSOR_INFO cursorInfo;
            GetConsoleCursorInfo(buffers[i], &cursorInfo);
            cursorInfo.bVisible = FALSE;
            SetConsoleCursorInfo(buffers[i], &cursorInfo);
        }
}
void ConsoleInterface::move_cursor(int x, int y){
        COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
        SetConsoleCursorPosition(buffers[active], pos);
}
void ConsoleInterface::showCursor(){
        for (int i = 0; i < 2; i++)
        {
            CONSOLE_CURSOR_INFO cursorInfo;
            GetConsoleCursorInfo(buffers[i], &cursorInfo);
            cursorInfo.bVisible = TRUE;
            SetConsoleCursorInfo(buffers[i], &cursorInfo);
        }
    }
void ConsoleInterface::swapBuffers(){
        active = 1 - active;
        SetConsoleActiveScreenBuffer(buffers[active]);
}