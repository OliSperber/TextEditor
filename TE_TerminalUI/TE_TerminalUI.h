#ifndef TE_TERMINALUI_H
#define TE_TERMINALUI_H

extern int UI_CURSOR_ROW;
extern int UI_CURSOR_COLUMN;
extern int UI_CURSOR_PREFERRED_COLUMN;

void UI_Load();

void UI_LoadLine(int row);
void UI_DeleteLine(int row);
void UI_AddLine(int row);

void UI_MoveCursorRaw(int row, int col);
void UI_MoveCursor();
void UI_MoveCursorUp();
void UI_MoveCursorDown();
void UI_MoveCursorLeft();
void UI_MoveCursorRight();
int CurrentLineLength();


void UI_ClearScreen();

#endif
