#ifndef TE_BUFFEREDITOR_H
#define TE_BUFFEREDITOR_H

#include <stdio.h>

extern char** TEXTBUFFER;
extern int LINESCOUNT;

void BUFFEREDITOR_LoadFullBuffer(FILE* file);

void BUFFEREDITOR_InsertChar(char c);
void BUFFEREDITOR_InsertEnter();
void BUFFEREDITOR_InsertBackspace();

#endif
