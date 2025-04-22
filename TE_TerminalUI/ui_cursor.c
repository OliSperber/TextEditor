#include "TE_BufferEditor.h"
#include "TE_TerminalUI.h"

#include <string.h>
#include <windows.h>

int UI_CURSOR_ROW = 0;
int UI_CURSOR_COLUMN = 0;
int UI_CURSOR_PREFERRED_COLUMN = 0;

void UI_MoveCursorRaw(int row, int col){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { col, row }; // 0-based
    SetConsoleCursorPosition(hConsole, pos);
}

void UI_MoveCursor(){
    UI_MoveCursorRaw(UI_CURSOR_ROW, UI_CURSOR_COLUMN);
}

void UI_MoveCursorUp(){
    if(UI_CURSOR_ROW <= 0)
        return;

    UI_CURSOR_ROW--;
    int NewLineLength = CurrentLineLength();

    if(UI_CURSOR_PREFERRED_COLUMN > NewLineLength)
        UI_CURSOR_COLUMN = NewLineLength; 
    else
        UI_CURSOR_COLUMN = UI_CURSOR_PREFERRED_COLUMN;

    UI_MoveCursor();
}

void UI_MoveCursorDown(){
    if(UI_CURSOR_ROW >= LINESCOUNT - 1)
        return;

    UI_CURSOR_ROW++;
    int NewLineLength = CurrentLineLength();

    if(UI_CURSOR_PREFERRED_COLUMN > NewLineLength)
        UI_CURSOR_COLUMN = NewLineLength; 
    else
        UI_CURSOR_COLUMN = UI_CURSOR_PREFERRED_COLUMN;


    UI_MoveCursor();
}

void UI_MoveCursorLeft(){
    if(UI_CURSOR_COLUMN <= 0){ // At start of line
        if(UI_CURSOR_ROW <= 0)
            return;

        UI_CURSOR_ROW--;
        UI_CURSOR_COLUMN = CurrentLineLength();
        UI_CURSOR_PREFERRED_COLUMN = UI_CURSOR_COLUMN;
    } else { // default
        UI_CURSOR_COLUMN--;
        UI_CURSOR_PREFERRED_COLUMN = UI_CURSOR_COLUMN;
    }

    UI_MoveCursor();
}

void UI_MoveCursorRight(){
    if(UI_CURSOR_COLUMN == CurrentLineLength()){
        if(UI_CURSOR_ROW >= LINESCOUNT - 1)
            return;

        UI_CURSOR_ROW++;
        UI_CURSOR_COLUMN = 0;
        UI_CURSOR_PREFERRED_COLUMN = 0;
    }
    else{
        UI_CURSOR_COLUMN++;
        UI_CURSOR_PREFERRED_COLUMN = UI_CURSOR_COLUMN;
    }

    UI_MoveCursor();
}

int CurrentLineLength(){
    return strlen(TEXTBUFFER[UI_CURSOR_ROW]) - 1;
};

