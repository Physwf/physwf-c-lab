#include "net.h"
#include <stdio.h>
#include <windows.h>


SOCKET server;
Connection clients[MAX_CONN];

int num_clients;

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
	printf("init net\n");
	WSADATA wsa;
	if(WSAStartup(MAKEWORD(2,2),&wsa) != 0)
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
	unsigned long non_block = 1;
	if( ioctlsocket(server, FIONBIO, &non_block) == SOCKET_ERROR)
	{
		printf("ioctlsocket() failed with error %d\n");
		exit(-1);
	}
}

void net_accept()
{
	FD_ZERO(&rset);
	FD_SET(server,&rset);
	if( select(0, &rset, NULL, NULL, NULL) == SOCKET_ERROR)
	{
		printf("server socket:select return error!\n");
		return;
	}
	if(FD_ISSET(server,&rset))
	{
		if( (client_temp = accept(server,NULL,NULL) ) != INVALID_SOCKET )
		{
			unsigned long non_block = 1;
			if( ioctlsocket(client_temp,FIONBIO, &non_block) == SOCKET_ERROR )
			{
				printf("ioctlsocket() failed with error %d\n",WSAGetLastError());
				return;
			}
			int i = get_free_index();
			if(i>0)
			{
				clients[i].socket = client_temp;
				clients[i].state = STATE_HOLD;
				num_clients++;
				//onAccepted, notify business layer
			}
		}
		else
		{
			printf("accept error!\n");
		}
	}
}

void net_read_and_write_client()
{
	FD_ZERO(&rset);
	FD_ZERO(&wset);
	
	for(int i=0;i<MAX_CONN;i++)
	{
		if(clients[i].state == STATE_HOLD)
		{
			FD_SET(clients[i].socket,&rset);
			FD_SET(clients[i].socket,&wset);
			if( select(0,&rset, &wset, NULL, NULL) == SOCKET_ERROR )
			{
				printf("client socket:select return error!\n");
				return;
			}
			if(FD_ISSET(clients[i].socket,&rset))
			{
				int len = READ_BUFFER_SIZE - clients[i].readBufAvaliable;
				char* avaliableBuffer = clients[i].readBuffer+clients[i].readBufAvaliable;
				if(len > 0)
				{
					int rc = recv(clients[i].socket,avaliableBuffer,len,0);
					if(rc > 0)
					{
						clients[i].readBufAvaliable += rc;
					}
					else if(rc == 0)
					{
						clients[i].state = STATE_CLOSED;
					}
					else
					{
						printf("recv error:%d!\n",WSAGetLastError());
					}
				}
			}
			if(FD_ISSET(clients[i].socket,&wset))
			{
				int len = clients[i].writeBufAvaliable;
				char* sendBuffer = clients[i].writeBuffer;
				if(len > 0)
				{
					int rc = send(clients[i].socket,sendBuffer,len,0);
					if(rc > 0)
					{
						int left = len - rc;
						if(left > 0)
							memcpy(clients[i].writeBuffer,clients[i].writeBuffer+rc,left);
						clients[i].writeBufAvaliable -= rc;
					}
				}
			}
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
		}
	}
}

void net_run()
{
	if(num_clients < MAX_CONN)
		net_accept();
	net_read_and_write_client();
	net_clean();
}