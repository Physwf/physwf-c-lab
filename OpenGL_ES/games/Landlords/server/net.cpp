#include "net.h"
#include <stdio.h>
#include <windows.h>


SOCKET server;
int flags[MAX_CONN];// 0 free, 1 hold, 
SOCKET clients[MAX_CONN];

int num_clients;

FD_SET rset;
FD_SET wset;
FD_SET eset;

SOCKET client_temp;

int get_free_index()
{
	for(int i=0;i<MAX_CONN;i++)
	{
		if(flags[i] == 0) return i;
	}
	return -1;
}

void net_init()
{
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2),$wsa) != 0)
	{
		printf("Socket init failed!\n");
		exit(-1);
	}
	if( (server = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) == INVALID_SOCKET)
	{
		printf("Create Socket failed!\n");
		exit(-1);
	}
	
	struct sockaddr_in server_addr;
	memset(&server_addr,0,sizeof(sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(10000);
	
	if(bind(server, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
	{
		printf("Bind socket error!\n");
		exit(-1);
	}
	
	if(listen(server,SOMAXCONN) == SOCKET_ERROR)
	{
		printf("Listen error!\n");
		exit(-1);
	}
}

void net_accept()
{
	FD_ZERO(&rset);
	FD_SET(server,&rset);
	if(FD_ISSET(server,&rset))
	{
		if( (client_temp = accept(server,NULL,NULL) ) != INVALID_SOCKET )
		{
			int non_block = 1;
			if( ioctlsocket(client_temp,FIONBIO, &nonblock) == SOCKET_ERROR )
			{
				printf("ioctlsocket() failed with error %d\n",WSAGetLastError());
				return;
			}
			int i = get_free_index();
			if(i>0)
			{
				clients[i] = clinent_temp;
				//onAccepted, notify business layer
			}
		}
	}
}

void net_read_and_write_client()
{
	for(int i=0;i<MAX_CONN;i++)
	{
		if(flags[i] == FLAG_HOLD)
		{
		}
	}
}

void net_run()
{
	if(num_clinets < MAX_CONN0)
		net_accept();
	
}