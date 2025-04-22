#include "TE_FileManager.h"
#include "TE_TerminalUI.h"
#include "TE_InputHandler.h"
#include "TE_BufferEditor.h"

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

int main(int argc, char *argv[]) {
    // Checking if file is passed as argument
    if (argc != 2) {
        printf("ERROR: Geen bestandsnaam gegeven");
        return 1;
    }

    // Loading in or creating file
    SELECTEDFILE = argv[1];
    FILEMANAGER_LoadFile();

    // Setting curson to left up corner
    UI_MoveCursorRaw(0, 0);

    // Starting receiving input;
    INPUTHANDLER_StartDetectingInput();

    return 0;
}
