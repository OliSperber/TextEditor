#ifndef TE_BUFFEREDITOR_H
#define TE_BUFFEREDITOR_H

char** TEXTBUFFER;

void BUFFEREDITOR_LoadFullBuffer();

void BUFFEREDITOR_InsertChar(char c);
void BUFFEREDITOR_InsertEnter();
void BUFFEREDITOR_InsertBackspace();

#endif
