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

void BUFFEREDITOR_InsertChar(char c){
    // Resizing string to make room for the new char
    int newLength = strlen(TEXTBUFFER[UI_CURSOR_ROW]) + 1;
    char* tempLine = realloc(TEXTBUFFER[UI_CURSOR_ROW], newLength + 1);
    if(tempLine == NULL){
        UI_ClearScreen();
        printf("Error while reallocating string for new char");
        return;
    }
    TEXTBUFFER[UI_CURSOR_ROW] = tempLine;

    // Adding new char to string
    for(int i = newLength - 1; i > UI_CURSOR_COLUMN; i--)
        TEXTBUFFER[UI_CURSOR_ROW][i] = TEXTBUFFER[UI_CURSOR_ROW][i - 1];

    TEXTBUFFER[UI_CURSOR_ROW][UI_CURSOR_COLUMN] = c;
    TEXTBUFFER[UI_CURSOR_ROW][newLength] = '\0';
    
    // Reload line
    UI_LoadLine(UI_CURSOR_ROW);

    // Moving Cursor
    UI_CURSOR_COLUMN++;
    UI_CURSOR_PREFERRED_COLUMN++;
    UI_MoveCursor();
}



void BUFFEREDITOR_InsertEnter(){
    // Add 1 line to TextBuffer
    LINESCOUNT++;
    char** temp_textbuffer = realloc(TEXTBUFFER, LINESCOUNT * sizeof(char*));
    if (temp_textbuffer == NULL)
        return;
    TEXTBUFFER = temp_textbuffer;
    
    // Move All lines down
    for (int i = LINESCOUNT - 1; i > UI_CURSOR_ROW; i--)
        TEXTBUFFER[i] = TEXTBUFFER[i - 1];

    // Create new line
    int currentLineLength = strlen(TEXTBUFFER[UI_CURSOR_ROW]);
    int newLineLength = currentLineLength - UI_CURSOR_COLUMN;
    char* newLine = malloc(newLineLength + 1);
    if (newLine == NULL) return;
    TEXTBUFFER[UI_CURSOR_ROW + 1] = newLine;

    for (int i = UI_CURSOR_COLUMN; i < currentLineLength; i++)
        TEXTBUFFER[UI_CURSOR_ROW + 1][i - UI_CURSOR_COLUMN] = TEXTBUFFER[UI_CURSOR_ROW][i];

    TEXTBUFFER[UI_CURSOR_ROW + 1][newLineLength] = '\0';

    // Edit line above newline
    char* templine = realloc(TEXTBUFFER[UI_CURSOR_ROW], UI_CURSOR_COLUMN + 2); 
    if (templine == NULL) return;
    templine[UI_CURSOR_COLUMN] = '\n';
    templine[UI_CURSOR_COLUMN + 1] = '\0';
    TEXTBUFFER[UI_CURSOR_ROW] = templine;
    
    // Reload all lines
    UI_DeleteLine(UI_CURSOR_ROW, currentLineLength);
    for(int i = UI_CURSOR_ROW; i < LINESCOUNT; i++){
        if(i != LINESCOUNT - 1)
            UI_DeleteLine(i, strlen(TEXTBUFFER[i + 1]));

        UI_LoadLine(i);
    }
    
    // Move Cursor
    UI_CURSOR_ROW++;
    UI_CURSOR_COLUMN = 0;
    UI_CURSOR_PREFERRED_COLUMN = 0;
    UI_MoveCursor();
}

void BUFFEREDITOR_InsertBackspace(){
    int currentLineLength = strlen(TEXTBUFFER[UI_CURSOR_ROW]);

    if(UI_CURSOR_COLUMN > 0){// Cursor is not at the beginning
        // Resizing to remove 1 char
        char* tempLine = realloc(TEXTBUFFER[UI_CURSOR_ROW], currentLineLength);
        if(tempLine == NULL) return;
        TEXTBUFFER[UI_CURSOR_ROW] = tempLine;

        // Rewriting line  to TEXTBUFFER
        for (int i = UI_CURSOR_COLUMN;i < currentLineLength - 2; i++)
                TEXTBUFFER[UI_CURSOR_ROW][i - 1] = TEXTBUFFER[UI_CURSOR_ROW][i];
        TEXTBUFFER[UI_CURSOR_ROW][currentLineLength - 2] = '\n';
        TEXTBUFFER[UI_CURSOR_ROW][currentLineLength - 1] = '\0';

        // Reloading edited line
        UI_DeleteLine(UI_CURSOR_ROW, currentLineLength);
        UI_LoadLine(UI_CURSOR_ROW);
        
        // Moving Cursor
        UI_CURSOR_COLUMN--;
        UI_CURSOR_PREFERRED_COLUMN--;
        UI_MoveCursor();
    }
    else{   // Cursor is at the beginning
        // Rewriting line above
        int originalLength = strlen(TEXTBUFFER[UI_CURSOR_ROW - 1]) - 1; // -1 to remove \n
        int lineLength = originalLength + strlen(TEXTBUFFER[UI_CURSOR_ROW]) + 1; // +1 to make room for \0
        
        char* tempLine = realloc(TEXTBUFFER[UI_CURSOR_ROW - 1], lineLength);
        if(tempLine == NULL) return;
        TEXTBUFFER[UI_CURSOR_ROW - 1] = tempLine;
        
        for (int i = originalLength; i <= lineLength; i++)
            TEXTBUFFER[UI_CURSOR_ROW - 1][i] = TEXTBUFFER[UI_CURSOR_ROW][i - originalLength];
        
        // Free current line memory
        free(TEXTBUFFER[UI_CURSOR_ROW]);
        TEXTBUFFER[UI_CURSOR_ROW] = NULL;

        
        // Move all lines in TEXTBUFFER
        LINESCOUNT--;
        for(int i = UI_CURSOR_ROW; i < LINESCOUNT; i++)
            TEXTBUFFER[i] = TEXTBUFFER[i + 1];
        TEXTBUFFER[LINESCOUNT] = NULL;
        
        // Reload lines in UI
        UI_DeleteLine(UI_CURSOR_ROW - 1, originalLength + 1); // reload line above
        UI_LoadLine(UI_CURSOR_ROW - 1);

        UI_DeleteLine(UI_CURSOR_ROW, lineLength - originalLength); // reload deleted line
        if (TEXTBUFFER[UI_CURSOR_ROW] != NULL) 
            UI_LoadLine(UI_CURSOR_ROW);

        for(int i = UI_CURSOR_ROW + 1; i < LINESCOUNT; i++){ // place all lines one up
            UI_DeleteLine(i, strlen(TEXTBUFFER[i - 1]));
            UI_LoadLine(i);
        }

        UI_DeleteLine(LINESCOUNT, strlen(TEXTBUFFER[LINESCOUNT - 1])); // delete last line
        
        // Move Cursor
        UI_CURSOR_ROW--;
        UI_CURSOR_COLUMN = originalLength;
        UI_CURSOR_PREFERRED_COLUMN = originalLength;
        UI_MoveCursor();
    }
        
}
