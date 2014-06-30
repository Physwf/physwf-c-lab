#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"
#include "game.h"
#include "services.h"


#define MAX_INPUT 64

#define GAME_START "start"

HANDLE inputThread;

char readBuffer[MAX_INPUT];

bool input_suspend;

void parseCards(char *str, int* ranks, int* num_cards)
{
	//Card cards[]
	char* token = strtok(str," ");
	while(token != NULL)
	{
		int rank = atoi(token);
		if(rank == 0) continue;
		ranks[(*num_cards)++] = rank;
	}
}

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
		case GAME_PHASE_WAIT_FOR_LOOT:
			{
				int score = atoi(str);
				if(score < 0) score = 0;
				if(score > 3) score = 3;
				send_loot_score(score);
			}
			break;
		case GAME_PHASE_WAIT_FOR_CARDS:
			{
				int ranks[20];
				int num_cards = 0;
				parseCards(str,ranks,&num_cards);
				send_play_cards(ranks,num_cards);
			}
			break;
		case GAME_PHASE_WAIT_FOR_OTHERS:
			printf("It is not you turn! Please wait.");
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

