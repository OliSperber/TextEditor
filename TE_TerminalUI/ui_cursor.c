#include "TE_BufferEditor.h"
#include "TE_TerminalUI.h"

#include <string.h>
#include <windows.h>

int* UI_CURSOR_ROW = 0;
int* UI_CURSOR_COLUMN = 0;
int* UI_CURSOR_PREFERREF_COLUMN = 0;

void UI_MoveCursor(int row, int colum){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { colum, row }; // 0-based
    SetConsoleCursorPosition(hConsole, pos);
}
void UI_MoveCursorUp(){


    UI_MoveCursor(*UI_CURSOR_ROW, *UI_CURSOR_COLUMN);
}

void UI_MoveCursorDown(){
    UI_MoveCursor(*UI_CURSOR_ROW, *UI_CURSOR_COLUMN);
}

void UI_MoveCursorLeft(){
    if(*UI_CURSOR_COLUMN <= 0){ // At start of line
        if(*UI_CURSOR_COLUMN <= 0)
            return;

        *UI_CURSOR_ROW = *UI_CURSOR_ROW - 1;
        *UI_CURSOR_COLUMN = CurrentLineLength();
        *UI_CURSOR_PREFERREF_COLUMN = *UI_CURSOR_COLUMN;
    } else { // default
        *UI_CURSOR_COLUMN = *UI_CURSOR_COLUMN - 1;
        *UI_CURSOR_PREFERREF_COLUMN = *UI_CURSOR_COLUMN;
    }

    UI_MoveCursor(*UI_CURSOR_ROW, *UI_CURSOR_COLUMN);
}

void UI_MoveCursorRight(){
    UI_MoveCursor(*UI_CURSOR_ROW, *UI_CURSOR_COLUMN);
}

int CurrentLineLength(){
    return strlen(TEXTBUFFER[*UI_CURSOR_ROW]);
};

