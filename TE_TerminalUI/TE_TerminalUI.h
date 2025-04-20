#ifndef TE_TERMINALUI_H
#define TE_TERMINALUI_H

char** UI_TEXTBUFFER;
int* UI_ROW = 0;
int* UI_COLUMN = 0;

void UI_Load();

void UI_LoadLine(int row);
void UI_DeleteLine(int row);
void UI_AddLine(int row);

void UI_MoveCursor(int row, int column);

#endif
