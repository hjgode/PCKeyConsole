#include "stdafx.h"

struct time {
  unsigned char  ti_min;   /* minutes */
  unsigned char  ti_hour;  /* hours */
  unsigned char  ti_hund;  /* hundredths of seconds */
  unsigned char  ti_sec;   /* seconds */
};
void gettime( struct time *t)
{
  SYSTEMTIME st;
  GetSystemTime(&st);
  t->ti_min=st.wMinute;
  t->ti_hour=st.wHour;
  t->ti_hund=st.wMilliseconds;
  t->ti_sec=st.wSecond;
}
char RetChar(INPUT_RECORD &InRec)
{
 	 return InRec.Event.KeyEvent.uChar.AsciiChar;
}

UINT bioskey(int num)
{
 	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD InRec;
    DWORD NumRead;
 	ReadConsoleInput(hIn,&InRec,1,&NumRead);
 	if(num==0)
 	{
 	  while(InRec.EventType!=KEY_EVENT || InRec.Event.KeyEvent.bKeyDown==FALSE)
 	  ReadConsoleInput(hIn,&InRec,1,&NumRead);
 	  return MAKEWORD((BYTE)InRec.Event.KeyEvent.uChar.AsciiChar,(BYTE)InRec.Event.KeyEvent.wVirtualScanCode);
    }
    else
    if(num==1)
    {
       if(InRec.EventType==KEY_EVENT)
       return MAKEWORD((BYTE)InRec.Event.KeyEvent.uChar.AsciiChar,(BYTE)InRec.Event.KeyEvent.wVirtualScanCode);
       else
       return FALSE;
    }
    else
    return FALSE;
}
int Getch()
{
 	return bioskey(0);
}
void clrscr()
{
    system("cls"); //lazy me :P/>
}
int wherex()
{
  	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO ccinfo;
   GetConsoleScreenBufferInfo(hOut,&ccinfo);
	return ccinfo.dwCursorPosition.X+1;
}
int wherey()
{
  	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO ccinfo;
   GetConsoleScreenBufferInfo(hOut,&ccinfo);
	return ccinfo.dwCursorPosition.Y+1;
}
void gotoxy(int x,int y)
{
	COORD coord = {x-1,y-1};
	SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void textcolor(int color)
{
 	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  	SetConsoleTextAttribute(hOut,color);
}
enum {_NOCURSOR=0,_NORMALCURSOR,_SOLIDCURSOR};

void _setcursortype(int Type)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ccinfo;
	if(Type==0)
	  ccinfo.bVisible=false;
	else
	{
	  ccinfo.bVisible=true;
	  if(Type==1)
	  ccinfo.dwSize=1;
	  else
	  ccinfo.dwSize=100;
	}
	SetConsoleCursorInfo(hOut,&ccinfo);
}
int getmouseinfo(int &x,int &y,int &mousebutton)
{
   	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD InRec;
    DWORD NumRead;
 	ReadConsoleInput(hIn,&InRec,1,&NumRead);
	if(InRec.EventType==MOUSE_EVENT)
	{
	   x=InRec.Event.MouseEvent.dwMousePosition.X;
	   y=InRec.Event.MouseEvent.dwMousePosition.Y;
	   if(InRec.Event.MouseEvent.dwButtonState==RIGHTMOST_BUTTON_PRESSED)
	     mousebutton=0x02;
	   else
	   if(InRec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED)
	   	 mousebutton=0x01;
	   else
         mousebutton=InRec.Event.MouseEvent.dwButtonState;
	   return 1;
	}
	else
	{
	   x=0,y=0,mousebutton=0;
	   WriteConsoleInput(hIn,&InRec,1,&NumRead);
	   return 0;
	}
}
int random(int num)
{
    return rand()%num;
}

int cprintf(char str[])
{
   HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
   DWORD NumberOfCharsWritten;
   WriteConsole(hOut,(void*)str,strlen(str),&NumberOfCharsWritten,NULL);
   return NumberOfCharsWritten;
}
bool Kbhit()
{
   HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
   INPUT_RECORD InRec;
   DWORD NumRead;
   PeekConsoleInput(hIn,&InRec,1,&NumRead);
   if(InRec.EventType==KEY_EVENT)
	 return true;
   else
   {
   	 //WriteConsoleInput(hIn,&InRec,1,&NumRead);
	 return false;
   }
}
void Delay(int millisec)
{
    Sleep(millisec);
}
void textmode(int type)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT sr={0,0,79,49};
 	SetConsoleWindowInfo(hOut,true,&sr);
	COORD coord;
	coord.X=80; coord.Y=50;
	SetConsoleScreenBufferSize(hOut,coord);
}
