#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#define RECV_BUFFER_SIZE 8192
#include <winbase.h>

#include "svnNotifySDK.h"
#include "resource.h"

/**
监视线程函数 
**/
DWORD WINAPI DirMonitor(LPVOID param)
{
	MY_ARG arg = (MY_ARG ) param;
	SOCKET cntSocket = arg->socket;
	if(cntSocket == INVALID_SOCKET) 
	{
		printf("Invalid Socket!");
		return 1;
	}
	TCHAR msgBuf[20];
	DWORD size = sizeof(msgBuf);
	GetComputerName(msgBuf,&size);//获取计算机名
	printf(msgBuf);
	printf("\n");
	// 获取要监视的目录句柄
	HANDLE hDir;
	LPSTR dirPath = "../svnLog";
	hDir = CreateFile(dirPath,
						GENERIC_READ,
						FILE_SHARE_READ | FILE_SHARE_WRITE,
						NULL,
						OPEN_EXISTING,
						FILE_FLAG_BACKUP_SEMANTICS,NULL);
						
	//监视
	char notify[1024];
	DWORD cbBytes;
	FILE_NOTIFY_INFORMATION *pnotify = (FILE_NOTIFY_INFORMATION *) notify;
	FILE_NOTIFY_INFORMATION *temp;
	BOOL ret;
	LPOVERLAPPED lpOverlapped;
	DWORD numBytes;

	while((arg->isOver)==0)
	{
		// if(!GetOverlappedResult(hDir,lpOverlapped,&numBytes,FALSE))
		// {
			// continue;
		// }
			
		ret = ReadDirectoryChangesW(hDir,&notify,sizeof(notify),FALSE,
									 FILE_NOTIFY_CHANGE_FILE_NAME,
									&cbBytes,NULL,NULL);
		printf("DirMonitor %d\n",arg->isOver);
		if(!ret) continue;
		temp = pnotify;
		printf("action:%d\n",temp -> Action);
		switch(temp -> Action)
		{
			case FILE_ACTION_RENAMED_OLD_NAME:
				printf("modified\n");
				DWORD bytesSend = send(cntSocket,msgBuf,lstrlen(msgBuf)+1,0);
				if(bytesSend != SOCKET_ERROR)
				{
					printf("sending %d \n",bytesSend);
					// PostMessage(FindWindow(NULL,"SVNNotify"),WM_SOCK_RECV,NULL,(LPARAM)msgBuf);
				}
				else 
				{
					printf("Error Sending %d\n",GetLastError());
				}
		}
	}
	printf("DirMonitor end \n");
	return 0;
	
}

/**
接收线程函数
**/
DWORD WINAPI RecvProc(LPVOID param)
{
	MY_ARG arg = (MY_ARG) param;
	SOCKET clientSocket = arg->socket;
	// PCOPYDATASTRUCT data = (PCOPYDATASTRUCT) HeapAlloc(GetProcessHeap(),0,sizeof(PCOPYDATASTRUCT));
	LPVOID recvBuffer;
	int bytesRecv=1;
	recvBuffer = HeapAlloc(GetProcessHeap(),0,RECV_BUFFER_SIZE+1);
	while((arg->isOver)==0)
	{
		printf("start recving\n");
		if(bytesRecv != SOCKET_ERROR)
		{
			bytesRecv =  recv(clientSocket,(char *) recvBuffer,RECV_BUFFER_SIZE,0);
			PostMessage(FindWindow(NULL,"SVNNotify"),WM_SOCK_RECV,NULL,(LPARAM)recvBuffer);
			printf("Bytes Recv: %ld \n",bytesRecv);
		}
	}
	HeapFree(GetProcessHeap(),0,recvBuffer);
	printf("RecvProc end \n");
	return 0;
}

/**
建立socket
**/
SOCKET EstablishSocket(void)
{
	/*
	启动
	*/
	WSADATA wsaData; //结构，WSAStartup用与其加载的库版本有关的信息填充这个结构
	int ret = WSAStartup(MAKEWORD(2,2),&wsaData);//第二个参数为指针类型，所以需要进行取地址运算
	if(ret !=0 ) 
	{
		printf("Startup Error %d \n",ret);
		return INVALID_SOCKET;
	}	
	
	/*
	*创建套接字
	*/
	SOCKET s;
	s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);//三个参数分别是 协议地址族 socket类型 协议类型
	
	/*
	 配置地址
	*/
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(10000);
	addr.sin_addr.s_addr = inet_addr("192.168.20.165");//"192.168.20.165"
	
	/*
	连接
	*/
	ret = connect(s,(SOCKADDR*) &addr,sizeof(addr));//  三个参数分别是 套接字对象 地址信息 地址大小
	if(ret == SOCKET_ERROR)
	{
		printf("Connect Error! %d \n",ret);
		WSACleanup();
		return INVALID_SOCKET;
	}	
	/*
	监控
	*/
	/*///////////////////////////////////////////////////////////////////
	DWORD tId[2];
	HANDLE  hThread[2];
	hThread[0] = CreateThread(NULL,0,DirMonitor,(LPVOID) s,0,&tId[0]);
	hThread[1] = CreateThread(NULL,0,RecvProc,(LPVOID) s,0,&tId[1]);
	//////////////////////////////////////////////////////////////////////
	// WaitForSingleObject(hThread,INFINITE);
	WaitForMultipleObjects(2,hThread,TRUE,INFINITE);
	*/
	/*
	接收
	*/
	
	/*
	退出程序
	*/
	// HeapFree(GetProcessHeap(),0,recvBuffer);
	// WSACleanup();
	return s;

}