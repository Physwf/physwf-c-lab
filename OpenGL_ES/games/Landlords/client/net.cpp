#include <stdlib.h>
#include <stdio.h>
#include <log/Log.h>
#include "net.h"
#include "../shared/common.h"
#include "../shared/msg.h"

Connection conn;
FD_SET rset;

HANDLE hNetThread;

void net_read();

DWORD WINAPI net_thread(LPVOID pParam)
{
	while(true)
	{
		net_read();
	}
	return 0;
}

void net_init()
{
	WSADATA wsa;
	if( WSAStartup(MAKEWORD(2,2), &wsa) != 0)
	{
		printf("Socket init failed!\n");
		exit(-1);
	}
	if( (conn.socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		printf("Create Socket Error!\n");
		exit(-1);
	}
	
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(10000);
	
	if( connect(conn.socket, (SOCKADDR *) &addr, sizeof(addr) ) == SOCKET_ERROR )
	{
		printf("connect failed!\n");
		exit(-1);
	}
	
	hNetThread = CreateThread(NULL,0,net_thread,NULL,0,NULL);
	// WaitForSingleObject(hNetThread, INFINITE);
	Log::info("log after wait");
}

void net_read()
{
	FD_ZERO(&rset);
	
	FD_SET(conn.socket,&rset);
	
	if( select(0, &rset, NULL, NULL, NULL) == SOCKET_ERROR)
	{
		Log::info("select return error!");
	}
	
	if(FD_ISSET(conn.socket,&rset))
	{
		int len = READ_BUFFER_SIZE - conn.readBufAvaliable;
		char* avaliableBuf = conn.readBufAvaliable + conn.readBuffer;
		
		if(len > 0)
		{
			
			int rc = recv(conn.socket, avaliableBuf, len, 0);
			if(rc > 0)
			{
				EnterCriticalSection(&CS);
				conn.readBufAvaliable += rc;
				Log::info("data recv!len:%d",rc);
				LeaveCriticalSection(&CS);
			}
			else if(rc == 0)
			{
				
			}
			else
			{
				
			}
			
		}
	}
}