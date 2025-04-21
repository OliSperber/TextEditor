#include "TE_TerminalUI.h"
#include "TE_BufferEditor.h"

void UI_Load(){
    UI_ClearScreen();

    for(int i = 0; i < LINESCOUNT; i++ ){
        printf("%s", TEXTBUFFER[i]);
    }
}
void UI_LoadLine(int row){}
void UI_DeleteLine(int row){}
void UI_AddLine(int row){}

