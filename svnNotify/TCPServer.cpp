
#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define DEFAULT_PORT "10000"
#define MAX_REQUEST 1024
#define BUF_SIZE 4096

int _cdecl main(void)
{
	WSADATA wsadata;
	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;
	struct addrinfo *result=NULL,hints;
	int iResult;
	
	iResult = WSAStartup(MAKEWORD(2,2),&wsadata);
	if(iResult !=0 )
	{
		printf("WSAStartup failed:d%\n",iResult);
		return 1;
	}
	
	ZeroMemory(&hints,sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	
	iResult = getaddrinfo(NULL,DEFAULT_PORT,&hints,&result);
	
	if(iResult !=0 )
	{
		printf("getaddrinfo failed: %d\n",iResult);
		WSACleanup();
		return 1;
	}
	
	ListenSocket = socket(result->ai_family,result->ai_socktype,result->ai_protocol );
	
	 if(ListenSocket == INVALID_SOCKET)
	 {
		printf("socket failed: %d\n",iResult);
		WSACleanup();
		return 1;
	 }
	 
	 iResult = bind(ListenSocket,result->ai_addr,(int)result->ai_addrlen);
	 
	 if(iResult == SOCKET_ERROR)
	 {
		printf("bind failed: %d\n",iResult);
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	 }
	 
	 printf("bind\n");
	 
	 freeaddrinfo(result);
	 
	 iResult = listen(ListenSocket,SOMAXCONN);
	 
	 printf("start listen.....\n");
	 
	 if(iResult == SOCKET_ERROR)
	 {
		printf("listen failed: %d\n",iResult);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	 }
	 
	 while(1)
	 {
		printf("ready to accept....\n");
		ClientSocket = accept(ListenSocket,NULL,NULL);
		printf("accept a connection\n");
		
		if(ClientSocket == INVALID_SOCKET)
		{
			printf("accept failed: %d\n" , WSAGetLastError());
			closesocket(ListenSocket);
			break;
		}
		
	 }
	  
}