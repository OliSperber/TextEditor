#include "TE_InputHandler.h"
#include "TE_BufferEditor.h"
#include "TE_FileManager.h"

#include <conio.h>
#include <stdbool.h>

void INPUTHANDLER_StartDetectingInput(){
    char c;
    bool detecting = true;

    while(detecting){
        c = _getch();

        switch(c){
            case 19: // ctrl + s
                FILEMANAGER_SaveFile();
                break;
            case 17: // ctrl + q
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
