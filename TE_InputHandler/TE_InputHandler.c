#include "TE_InputHandler.h"
#include "TE_BufferEditor.h"
#include "TE_TerminalUI.h"
#include "TE_FileManager.h"

#include <conio.h>
#include <stdbool.h>

void INPUTHANDLER_StartDetectingInput(){
    char c;
    bool detecting = true;

    while(detecting){
        c = _getch();

        // Handling arrow keys
        if (c == 0 || c == 224 || c == -32) {

            char arrow = _getch();

            switch (arrow) {
                case 72: // up
                    UI_MoveCursorUp();
                    break;
                case 80: // down
                    UI_MoveCursorDown();
                    break;
                case 75: // left
                    UI_MoveCursorLeft();
                    break;
                case 77: // right
                    UI_MoveCursorRight();
                    break;
            }
        }
        // handling everything else
        else{
            switch(c){
                case 19: // ctrl + s
                    FILEMANAGER_SaveFile();
                    break;
                case 17: // ctrl + q
                    UI_ClearScreen();
                    detecting = false;
                    break;
                case '\r': // Enter
                    BUFFEREDITOR_InsertEnter();
                    break;
                case '\b': // Backspace
                case 127: 
                    BUFFEREDITOR_InsertBackspace();
                    break;
                default: // Insertng given char
                    BUFFEREDITOR_InsertChar(c);
                    break;
            }
        }
    }
}
