#include <stdio.h>
#include <stdlib.h>
#include <log/Log.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib,"ws2_32.lib")

SOCKET conn;
FILE* Log::mStream = NULL;

FD_SET rset;

void init()
{
	Log::init("LLclient.log");
	WSADATA wsa;
	if( WSAStartup(MAKEWORD(2,2), &wsa) != 0)
	{
		printf("Socket init failed!\n");
		exit(-1);
	}
	if( (conn = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
	{
		printf("Create Socket Error!\n");
		exit(-1);
	}
	
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(10000);
	
	if( connect(conn, (SOCKADDR *) &addr, sizeof(addr) ) == SOCKET_ERROR )
	{
		printf("connect failed!\n");
		exit(-1);
	}
	
	// closesocket(conn);
}

void net_read()
{
	FD_ZERO(&rset);
	
	FD_SET(conn,&rset);
	
	if( select(0, &rset, NULL, NULL, NULL) == SOCKET_ERROR)
	{
		Log::info("select return error!");
	}
	
	if(FD_ISSET(conn,&rset))
	{
		
	}
}

int main()
{
	init();
	while(true)
	{
		net_read();
		Sleep(10);
	}
	return 0;
}