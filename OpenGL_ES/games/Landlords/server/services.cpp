#include "net.h"
#include "services.h"
#include <Windows.h>
#include <stdio.h>
#include <log/Log.h>
#include "game.h"

char buffer[WRITE_BUFFER_SIZE];
HANDLE hNetThread;

DWORD WINAPI net_thread(PVOID pParam)
{
	net_run();
	return 0;
}

void init_service()
{
	Log::info("init services!");
	net_init();
	//create net thread
	hNetThread = CreateThread(NULL,0,net_thread,NULL,0,NULL);
	WaitForSingleObject(hNetThread,INFINITE);
}

void send_data(int pid)
{
	
}

void send_deal_result(PDealResult result)
{
	
}

void broadcast_loot_score(int who,int score)
{
	
}

void send_wait_for_loot(int who)
{
}

void send_play_start()
{
}



