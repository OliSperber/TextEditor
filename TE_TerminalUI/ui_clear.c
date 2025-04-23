#include "TE_TerminalUI.h"

#include <windows.h>

void UI_ClearScreen(){
    COORD coord = {0, 0};    // Coordinates to move the cursor to the top-left corner
    DWORD written;

    // Get the console handle
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Get console screen buffer size
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the console with spaces
    FillConsoleOutputCharacter(hConsole, ' ', consoleSize, coord, &written);
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, consoleSize, coord, &written);

    // Move the cursor to the top-left corner
    SetConsoleCursorPosition(hConsole, coord);
}
