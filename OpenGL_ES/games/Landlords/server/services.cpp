#include "net.h"
#include "services.h"
#include <Windows.h>

char buffer[WRITE_BUFFER_SIZE];
HANDLE hNetThread;

DWORD WINAPI net_thread(PVOID pParam)
{
	net_run();
	return 0;
}

void init_service()
{
	net_init();
	//create net thread
	hNetThread = CreateThread(NULL,0,net_thread,NULL,0,NULL);
}

void send_data(int pid)
{
	
}

void broadcast_loot_score(int who,int score)
{
	
}

void send_wait_for_loot(int who)
{
}


