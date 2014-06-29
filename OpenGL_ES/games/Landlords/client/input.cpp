#include <stdio.h>


#include "input.h"
#include "game.h"
#include "services.h"


#define MAX_INPUT 64

#define GAME_START "start"

HANDLE inputThread;

char readBuffer[MAX_INPUT];

bool input_suspend;

void parseInput(char *str)
{
	switch(game.phase)
	{
		case GAME_PHASE_WAIT_FOR_PLAYERS:
			if( strcmp(str,GAME_START) == 0 )
			{
				send_start_game();
			}
			break;
	}
	printf(str);
}

DWORD WINAPI console_input(LPVOID pParam)
{
	while(true)
	{
		fgets(readBuffer, MAX_INPUT, stdin);
		parseInput(readBuffer);
	}
}

void init_input()
{
	inputThread = CreateThread(NULL, 0, console_input, NULL, 0, NULL);
	SuspendThread(inputThread);
	input_suspend = true;
}

void wait_for_input()
{
	if(!input_suspend) return;
	ResumeThread(inputThread);
	input_suspend = false;
}

void suspend_input()
{
	if(input_suspend) return;
	SuspendThread(inputThread);
	input_suspend = true;
}

