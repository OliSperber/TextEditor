#ifndef TE_TERMINALUI_H
#define TE_TERMINALUI_H

int* UI_ROW = 0;
int* UI_COLUMN = 0;

void UI_Load();

void UI_LoadLine(int row);
void UI_DeleteLine(int row);
void UI_AddLine(int row);

void UI_MoveCursor(int row, int column);

void UI_ClearScreen();

#endif
