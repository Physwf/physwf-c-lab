#include "net.h"
#include "services.h"
#include <Windows.h>
#include <stdio.h>
#include <log/Log.h>
#include "game.h"
#include "../shared/msg.h"

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
	// WaitForSingleObject(hNetThread,INFINITE);
}

void send_data(int pid, unsigned short mid, char* data, int len)
{
	MsgHead head;
	head.msgid = mid;
	head.length = len;
	if(pid < NUM_PLAYERS)
	{
		if(clients[pid].state == STATE_HOLD)
		{
			send(clients[pid].socket,(char*)&head,len,0);
			send(clients[pid].socket,data,len,0);
		}
	}
}

void broadcast_data(unsigned short mid, char* data,int len)
{
	MsgHead head;
	head.msgid = mid;
	head.length = len + HEAD_LENGTH;
	for(int i=0;i<NUM_PLAYERS;i++)
	{
		if(clients[i].state == STATE_HOLD)
		{
			send(clients[i].socket, (char*)&head, HEAD_LENGTH, 0);
			send(clients[i].socket,data,len,0);
		}
	}
}

void broadcast_deal_result(PDealResult result)
{
	broadcast_data((int)MSG_NOTI_DEAL_RESULT_1000,(char*)result,sizeof(DealResult));
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



