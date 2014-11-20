#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

#define MAX_CONNCET 10000
#define RECV_BUFFER_SIZE 8192

SOCKET clientList[10];
int numClient = 0;
HANDLE hThreads[10];
DWORD tIds[10];

DWORD WINAPI RecvProc(LPVOID param)
{
	SOCKET cntSocket = (SOCKET) param;
	printf("Thread established ,id: %d\n",GetCurrentThreadId());
	if(cntSocket == INVALID_SOCKET)
	{
		printf("Invalid socket!\n");
	}
	LPVOID recvBuf = HeapAlloc(GetProcessHeap(),0,RECV_BUFFER_SIZE);
	int bytesRecv=1;
	while(1)
	{
		if (bytesRecv == SOCKET_ERROR)
		{
			printf("recv error!\n");
			printf("Error Num %d\n",GetLastError());
			break;
		}		
		printf("Ready to Recv!\n");
		bytesRecv = recv(cntSocket,(char *) recvBuf,RECV_BUFFER_SIZE,0);
		if(bytesRecv == 0)
		{
			char *msg = (char *) recvBuf;
			printf(msg);
			printf("\n");
		}
		else 
		{
			printf("recving----------------------(%d)\n",GetCurrentThreadId());
			char *msg = (char *) recvBuf;
			printf(msg);
			printf("-----------------------\n");
			for(int i=0;i<10;++i)
			{
				printf("%d\n",i);
				if(clientList[i] != cntSocket && clientList[i] != INVALID_SOCKET)
				{
					int bytesSend = send(clientList[i],msg,lstrlen(msg)+1,0);
					if(bytesSend == SOCKET_ERROR)
					{
						printf("send error%d\n",WSAGetLastError());
						clientList[i] = INVALID_SOCKET;
					}
					else
					{
						printf("%d was sent \n",bytesSend);
					}
					
				}
			}
			
		}
	}
	printf("Proc End! \n");
	return 0;
}
void main(void)
{
	/*
	启动
	*/
	int ret;
	WSADATA wsaData;
	ret = WSAStartup(MAKEWORD(2,2),&wsaData);
	if(ret !=0 )
	{
		printf("startup error %d\n",ret);
		return;
	}
	
	/* 
	创建socket
	 */
	SOCKET s;
	s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	
	/* 
	绑定
	 */
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(10000);
	addr.sin_addr.s_addr = inet_addr("192.168.20.165");//
	
	ret = bind(s,(SOCKADDR*) &addr,sizeof(addr));
	if(ret == SOCKET_ERROR)
	{
		printf("bind error %d\n",ret);
		return;
	}
	
	/* 
	监听
	*/
	ret = listen(s,MAX_CONNCET);
	if(ret == SOCKET_ERROR)
	{
		printf("listen error %d\n",ret);
		return;
	}
	
	/*
	接受
	*/
	SOCKET clientSock;
	SOCKADDR_IN clientAddr;
	int clientAddrLen;
	int i;
	for( i=0;i<10 ;++i)
	{
		clientList[i] =INVALID_SOCKET;
	}
	
	while(1)
	{
		printf("waitting next\n");
		
		clientSock = accept(s, NULL, NULL);
	
		if(clientSock != INVALID_SOCKET)
		{
			for( i=0;i<10 ;++i)
			{
				if( (clientList[i] == INVALID_SOCKET ) && (clientSock != INVALID_SOCKET)) 
				{
					clientList[i] = clientSock;
					hThreads[i] = CreateThread(NULL,0,RecvProc,(LPVOID) clientSock,0,&tIds[i]);
					clientSock = INVALID_SOCKET;
				}
				else 
				{
					numClient++;
				}
			}	
			WaitForMultipleObjects(numClient,hThreads,TRUE,INFINITE);
			numClient++;
			printf("client added,total: %d\n",numClient);
		}
		else
		{
			printf("accept error %d",WSAGetLastError());
		}
	}
	
	
}
