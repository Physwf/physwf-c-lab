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
	head.length = len+HEAD_LENGTH;
	Log::info("mid:%d,length:%d",mid,head.length);
	if(pid < NUM_PLAYERS)
	{
		if(clients[pid].state == STATE_HOLD)
		{
			send(clients[pid].socket,(char*)&head,HEAD_LENGTH,0);
			send(clients[pid].socket,data,len,0);
		}
	}
}

void broadcast_data(unsigned short mid, char* data,int len)
{
	MsgHead head;
	head.msgid = mid;
	head.length = len + HEAD_LENGTH;
	Log::info("mid:%d,length:%d",mid,head.length);
	for(int i=0;i<NUM_PLAYERS;i++)
	{
		if(clients[i].state == STATE_HOLD)
		{
			send(clients[i].socket, (char*)&head, HEAD_LENGTH, 0);
			send(clients[i].socket,data,len,0);
		}
	}
}

void send_ask_wait_more(int pid)
{
	MSG_ASK_WAIT_MORE msg;
	send_data(pid,MSG_NOTI_ASK_WAIT_MORE_1000, (char*)&msg,sizeof(MSG_ASK_WAIT_MORE));
}

void send_player_joined(int pid,int who)
{
	MSG_NOTI_PLAYER_JOIN msg;
	msg.playerId = who;
	send_data(pid,MSG_NOTI_PLAYER_JOIN_1001, (char*)&msg,sizeof(MSG_NOTI_PLAYER_JOIN));
}

void send_host_waiting_players(int pid)
{
	MSG_NOTI_HOST_WAIT_PLAYERS msg;
	send_data(pid,MSG_NOTI_HOST_WAIT_PLAYERS_1002, (char*)&msg,sizeof(MSG_NOTI_HOST_WAIT_PLAYERS));
}

void send_deal_result(int who, PDealResult result)
{
	MSG_NOTI_DEAL_RESULT msg;
	memcpy(&msg.result,result,sizeof(DealResult));
	send_data(who,(int)MSG_NOTI_DEAL_RESULT_1004, (char*)&msg, sizeof(MSG_NOTI_DEAL_RESULT));
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



