// PCkeyConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "ktools.h"

#define ARROW_UP    0x48
#define ARROW_LEFT  0x4B
#define ARROW_RIGHT 0x4D
#define ARROW_DOWN  0x50
#define ARROW_NONE  0x00
#define ESC_KEY     0x1B

	UINT count=0;

unsigned char getArrow() {
    if (kbhit()) {
        //we only want to get here if a key has been pressed...
        unsigned char ch = getch();
        if (ch == 0x00) {
            //first char is a zero so lets look at the next char....
            ch = getch();
            switch(ch) {
                case ARROW_UP:
                    return ch;
                case ARROW_LEFT:
                    return ch;
                case ARROW_RIGHT:
                    return ch;
                case ARROW_DOWN:
                    return ch;
                default:
                    return ARROW_NONE;
            }
        }
        return ch;
    }
    return ARROW_NONE;
}

void get_keypress(unsigned short& virtual_key, unsigned long& control_key)
{
	HANDLE input_handle = GetStdHandle(STD_INPUT_HANDLE); // handle to input/output buffer
	DWORD events = 0;			// how many events took place
	INPUT_RECORD input_record;	// a record of input events
	DWORD input_size = 1;		// how many characters to read

	bool not_a_keypress = true;

	do
	{
		// Stop from echoing.
		FlushConsoleInputBuffer(input_handle);
		ReadConsoleInput(input_handle, &input_record, input_size, &events);
		
		control_key = input_record.Event.KeyEvent.dwControlKeyState;
		
		/*
		if(control_key == NUMLOCK_ON)
		{ // Warn user to turn off scroll lock/num lock.
			//throw std::runtime_error("Please turn scroll lock/num lock off.");
			std::cout<<" NumLock ON";
		}else
			std::cout<<" NumLock OFF";
		if(control_key == SCROLLLOCK_ON){
			std::cout<<" ScrollLock ON";
		}else
			std::cout<<" ScrollLock OFF";
		*/

		if(input_record.EventType == KEY_EVENT)// && input_record.Event.KeyEvent.bKeyDown)
		{ // A key was pressed, so return it.
			count++;
			
			// 	std::cout<<"id\tevent\tcode\tdec\tscan\tscn\n";
			if(input_record.Event.KeyEvent.bKeyDown)
				std::cout<< count << "\t0x" << hex << input_record.Event.KeyEvent.wVirtualKeyCode << "\tdown\t" << dec << input_record.Event.KeyEvent.wVirtualKeyCode << "\t0x" << \
					hex << input_record.Event.KeyEvent.wVirtualScanCode << "\t" << dec <<input_record.Event.KeyEvent.wVirtualScanCode << std::endl;
			else
				std::cout<< count << "\t0x" << hex << input_record.Event.KeyEvent.wVirtualKeyCode << "\tup\t" << dec << input_record.Event.KeyEvent.wVirtualKeyCode << "\t0x" << \
					hex << input_record.Event.KeyEvent.wVirtualScanCode << "\t" << dec << input_record.Event.KeyEvent.wVirtualScanCode << std::endl;

			virtual_key = input_record.Event.KeyEvent.wVirtualKeyCode;
			// Already got control_key above.
			not_a_keypress = false;
		}
	} while(not_a_keypress);
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout<<"PCKeyConsole - show keypress values on screen\n";
	cout<<"press ESC key to quit\n";

	bool quit = false;
	unsigned short virtual_key = 0;
	unsigned long control_key = 0;
	std::cout<<"id\tevent\tcode\tdez\tscan\tscn\n";
	do
	{
		get_keypress(virtual_key, control_key);
		

		if(virtual_key == 0x27)
			bool b = true;

		if(virtual_key == VK_ESCAPE)
			quit = true;
		else if(control_key == SHIFT_PRESSED && virtual_key == 0x27)
			std::cout << "SHIFT + RIGHT ARROW KEY PRESSED!" << std::endl;
		else if(control_key == SHIFT_PRESSED && virtual_key == 'S')
			std::cout << "SHIFT + S KEY PRESSED!" << std::endl;
	} while(!quit);
	
	cout<<"press any key to exit\n";
	char chr=getch();

	return 0;

    unsigned char ch;
    while ((ch = getch()) != 27) {
        printf("%02X\n", ch);	//F1 -> 00 3B
    }
	return 0;
}

