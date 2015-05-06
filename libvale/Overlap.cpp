#include <WINSOCK2.H>
#include <stdio.h> 

#define PORT    5150
#define MSGSIZE 1024 

#pragma comment(lib, "ws2_32.lib") 

typedef struct
{
	WSAOVERLAPPED overlap;
	WSABUF        Buffer;
	char          szMessage[MSGSIZE];
	DWORD         NumberOfBytesRecvd;
	DWORD         Flags;
	SOCKET        sClient;
}PER_IO_OPERATION_DATA, *LPPER_IO_OPERATION_DATA;

DWORD WINAPI WorkerThread(LPVOID);
void CALLBACK CompletionROUTINE(DWORD, DWORD, LPWSAOVERLAPPED, DWORD);

SOCKET g_sNewClientConnection;
BOOL   g_bNewConnectionArrived = FALSE;

int main()
{
	int fd;
	WSADATA     wsaData;
	SOCKET      sListen;
	SOCKADDR_IN local, client;
	DWORD       dwThreadId;
	int         iaddrSize = sizeof(SOCKADDR_IN);
	sListen = fd;
	// Initialize Windows Socket library
	WSAStartup(0x0202, &wsaData);

	// Create listening socket
	sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// Bind
	local.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	local.sin_family = AF_INET;
	local.sin_port = htons(PORT);
	bind(sListen, (struct sockaddr *)&local, sizeof(SOCKADDR_IN));

	// Listen
	listen(sListen, 3);

	// Create worker thread
	CreateThread(NULL, 0, WorkerThread, NULL, 0, &dwThreadId);

	while (TRUE)
	{
		// Accept a connection
		g_sNewClientConnection = accept(sListen, (struct sockaddr *)&client, &iaddrSize);
		g_bNewConnectionArrived = TRUE;
		printf("Accepted client:%s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
	}
}

DWORD WINAPI WorkerThread(LPVOID lpParam)
{
	LPPER_IO_OPERATION_DATA lpPerIOData = NULL;

	while (TRUE)
	{
		if (g_bNewConnectionArrived)
		{
			// Launch an asynchronous operation for new arrived connection
			lpPerIOData = (LPPER_IO_OPERATION_DATA)HeapAlloc(
				GetProcessHeap(),
				HEAP_ZERO_MEMORY,
				sizeof(PER_IO_OPERATION_DATA));
			lpPerIOData->Buffer.len = MSGSIZE;
			lpPerIOData->Buffer.buf = lpPerIOData->szMessage;
			lpPerIOData->sClient = g_sNewClientConnection;
			WSARecv(lpPerIOData->sClient,
				&lpPerIOData->Buffer,
				1,
				&lpPerIOData->NumberOfBytesRecvd,
				&lpPerIOData->Flags,
				&lpPerIOData->overlap,
				CompletionROUTINE);
			g_bNewConnectionArrived = FALSE;
		}

		SleepEx(1000, TRUE);
	}
	return 0;
}

void CALLBACK CompletionROUTINE(DWORD dwError,
	DWORD cbTransferred,
	LPWSAOVERLAPPED lpOverlapped,
	DWORD dwFlags)
{
	LPPER_IO_OPERATION_DATA lpPerIOData = (LPPER_IO_OPERATION_DATA)lpOverlapped;

	if (dwError != 0 || cbTransferred == 0)
	{
		// Connection was closed by client
		closesocket(lpPerIOData->sClient);
		HeapFree(GetProcessHeap(), 0, lpPerIOData);
	}
	else
	{
		lpPerIOData->szMessage[cbTransferred] = '\0';
		send(lpPerIOData->sClient, lpPerIOData->szMessage, cbTransferred, 0);
		// Launch another asynchronous operation
		memset(&lpPerIOData->overlap, 0, sizeof(WSAOVERLAPPED));
		lpPerIOData->Buffer.len = MSGSIZE;
		lpPerIOData->Buffer.buf = lpPerIOData->szMessage;

		WSARecv(lpPerIOData->sClient,
			&lpPerIOData->Buffer,
			1,
			&lpPerIOData->NumberOfBytesRecvd,
			&lpPerIOData->Flags,
			&lpPerIOData->overlap,
			CompletionROUTINE);
	}
}