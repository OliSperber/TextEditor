#include "TE_FileManager.h"
#include "TE_BufferEditor.h"

#include <stdio.h>
#include <string.h>

char* SELECTEDFILE = "";

void FILEMANAGER_LoadFile(){
    FILE* file = fopen(SELECTEDFILE, "r");

    BUFFEREDITOR_LoadFullBuffer(file);

    fclose(file);
}

void FILEMANAGER_SaveFile(){
    FILE* file = fopen(SELECTEDFILE, "w");

    for(int i = 0; i < LINESCOUNT; i++){    
        // strip \n at the end to prevtn double spaces
        int length = strlen(TEXTBUFFER[i]);
        if(length > 0 && TEXTBUFFER[i][length - 1] == '\n')
            TEXTBUFFER[i][length - 1] = '\0';

        fprintf(file, "%s\n", TEXTBUFFER[i]);
    }

    fclose(file);
}
