#include "stdafx.h"

char RetChar(INPUT_RECORD &InRec);
UINT bioskey(int num);
int Getch();
void clrscr();
int cprintf(char str[]);
bool Kbhit();
void textmode(int type);