#include "TE_TerminalUI.h"
#include "TE_BufferEditor.h"

#include <windows.h>

void UI_Load(){
    UI_ClearScreen();

    for(int i = 0; i < LINESCOUNT; i++ ){
        printf("%s", TEXTBUFFER[i]);
    }
}

void UI_LoadLine(int row) {
    UI_MoveCursorRaw(row, 0);
    printf(TEXTBUFFER[row]);
}

void UI_DeleteLine(int row, int width) {
    UI_MoveCursorRaw(row, 0);
    for (int i = 0; i < width; i++) {
        putchar(' ');
    }
}

