#include "TE_BufferEditor.h"
#include "TE_TerminalUI.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char** TEXTBUFFER = NULL;
int LINESCOUNT = 0;

void BUFFEREDITOR_LoadFullBuffer(FILE* file){
    if(file == NULL) return;

    char buffer[1024];

    while(fgets(buffer, sizeof(buffer), file) != NULL) {
        // Add an extra string to TEXTBUFFER
        LINESCOUNT++;
        char** temp_textbuffer = realloc(TEXTBUFFER, LINESCOUNT * sizeof(char*));

        // Add text to new line
        if(temp_textbuffer != NULL){

            TEXTBUFFER = temp_textbuffer;

            TEXTBUFFER[LINESCOUNT - 1] = malloc(strlen(buffer) + 1);
            strcpy(TEXTBUFFER[LINESCOUNT - 1], buffer);
        }
        else{
            UI_ClearScreen();
            printf("Error while reallocating textBuffer");
            return;
        }
        
    }

    // Load the full buffer to UI
    UI_Load();
}

void BUFFEREDITOR_InsertChar(char c){}
void BUFFEREDITOR_InsertEnter(){}
void BUFFEREDITOR_InsertBackspace(){}
