#include <stdio.h>
#include <windows.h>

#include "input.h"

#define MAX_INPUT 100

char readBuffer[MAX_INPUT];

void dispatchInputEvent(char *buffer)
{
}

DWORD WINAPI console_input(DWORD pParam)
{
	while(true)
	{
		fgets(readBuffer, MAX_INPUT, stdin);
		dispatchInputEvent(readBuffer);
	}
}

