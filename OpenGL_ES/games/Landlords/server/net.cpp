#include "net.h"
#include <stdio.h>
#include <log/Log.h>
#include "listener.h"

SOCKET server;
Connection clients[MAX_CONN];

int num_clients = 0;

FD_SET rset;
FD_SET wset;
FD_SET eset;

SOCKET client_temp;

int get_free_index()
{
	for(int i=0;i<MAX_CONN;i++)
	{
		if(clients[i].state == STATE_FREE) return i;
	}
	return -1;
}

void net_init()
{
	Log::info("init net!");
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		Log::info("Socket init failed!");
		exit(-1);
	}
	if( (server = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == INVALID_SOCKET)
	{
		Log::info("Create Socket failed!");
		exit(-1);
	}
	
	struct sockaddr_in server_addr;
	memset(&server_addr,0,sizeof(sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(10000);
	
	if(bind(server, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
	{
		Log::info("Bind socket error!");
		exit(-1);
	}
	
	if(listen(server,SOMAXCONN) == SOCKET_ERROR)
	{
		Log::info("Listen error!");
		exit(-1);
	}
	unsigned long non_block = 1;
	if( ioctlsocket(server, FIONBIO, &non_block) == SOCKET_ERROR)
	{
		Log::info("ioctlsocket() failed with error %d!");
		exit(-1);
	}
}

void net_select()
{
	FD_ZERO(&rset);
	FD_ZERO(&wset);
	
	FD_SET(server,&rset);
	
	for(int i=0;i<MAX_CONN;i++)
	{
		if(clients[i].state == STATE_HOLD)
		{
			FD_SET(clients[i].socket,&rset);
			FD_SET(clients[i].socket,&wset);
		}
	}
	
	if( select(0, &rset, &wset, NULL, NULL) == SOCKET_ERROR)
	{
		Log::info("server socket:select return error!");
		return;
	}

	if(FD_ISSET(server,&rset))
	{
		if( (client_temp = accept(server,NULL,NULL) ) != INVALID_SOCKET )
		{
			unsigned long non_block = 1;
			if( ioctlsocket(client_temp,FIONBIO, &non_block) == SOCKET_ERROR )
			{
				Log::info("ioctlsocket() failed with error %d!",WSAGetLastError());
				return;
			}
			int i = get_free_index();
			if(i>=0)
			{
				clients[i].socket = client_temp;
				clients[i].state = STATE_HOLD;
				++num_clients;
				onPlayerJoin(num_clients,i);
				Log::info("client accepted, Total:%d!",num_clients);
				//onAccepted, notify business layer
			}
			else
			{
				Log::info("no free space to accept!");
			}
		}
	}
	
	for(int i=0;i<MAX_CONN;i++)
	{
		if(clients[i].state == STATE_HOLD)
		{
			if(FD_ISSET(clients[i].socket,&rset))
			{
				int len = READ_BUFFER_SIZE - clients[i].readBufAvaliable;
				char* avaliableBuffer = clients[i].readBuffer+clients[i].readBufAvaliable;
				if(len > 0)
				{
					EnterCriticalSection(&CS);//enter critical section
					int rc = recv(clients[i].socket,avaliableBuffer,len,0);
					if(rc > 0)
					{
						clients[i].readBufAvaliable += rc;
					}
					else if(rc == 0)
					{
						clients[i].state = STATE_CLOSED;
						Log::info("client closed!");
					}
					else
					{
						Log::info("recv error:%d!",WSAGetLastError());
						clients[i].state = STATE_CLOSED;
					}
					LeaveCriticalSection(&CS);//leave critical section
				}
			}
			return;
			/*
			if(FD_ISSET(clients[i].socket,&wset))
			{
				int len = clients[i].writeBufAvaliable;
				char* sendBuffer = clients[i].writeBuffer;
				
				if(len > 0)
				{
					EnterCriticalSection(&CS);//enter critical section
					int rc = send(clients[i].socket,sendBuffer,len,0);
					if(rc > 0)
					{
						int left = len - rc;
						if(left > 0)
							memcpy(clients[i].writeBuffer,clients[i].writeBuffer+rc,left);
						clients[i].writeBufAvaliable -= rc;
					}
					LeaveCriticalSection(&CS);//leave critical section
				}
			}
			*/
		}
	}
}

void net_clean()
{
	for(int i=0;i<MAX_CONN;i++)
	{
		if(clients[i].state != STATE_FREE && clients[i].state != STATE_HOLD)
		{
			clients[i].readBufAvaliable = 0;
			clients[i].writeBufAvaliable = 0;
			clients[i].state = STATE_FREE;
			Log::info("client cleaned!");
		}
	}
}

void net_run()
{
	while(true)
	{
		Log::info("loop");
		net_select();
		net_clean();
		Sleep(10);
	}
}