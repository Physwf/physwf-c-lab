// PswGame_LoginServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#define SQL_QUERY_SIZE      1000 // Max. Num characters for SQL Query passed in. 

int init();
DWORD WINAPI ReceProc(LPVOID params);

class RCPServer
{
	

public:
	//构造函数
	RCPServer()
	{
		rawSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
		if(rawSocket == INVALID_SOCKET)
		{
			printf("create error!");
		}
		//-------------------------
		// Set the socket I/O mode: In this case FIONBIO
		// enables or disables the blocking mode for the 
		// socket based on the numerical value of iMode.
		// If iMode = 0, blocking is enabled; 
		// If iMode != 0, non-blocking mode is enabled.
		u_long iMode = 0;
		ioctlsocket(rawSocket, FIONBIO, &iMode);
		if(initSock() == SOCKET_ERROR)
		{
			printf("bind error n");
		}
		printf("exe");
		return ;
	}
	 ~RCPServer()
	{
	}
	//开始监听
	int Listen()
	{
		return listen(rawSocket,5);
	}
	//开始接受
	int StartAccept()
	{
		acceptFlag = 1;
		numCon = 0;
		int clientAddrLen = sizeof(SOCKADDR);
		SOCKADDR_IN clientAddr;
		while(acceptFlag)
		{
			SOCKET clientSock = accept(rawSocket,(SOCKADDR*)&clientAddr,&clientAddrLen);
			clientList[numCon] = clientSock;
			hThreads[numCon] = CreateThread(NULL,0,ReceProc,(LPVOID) clientSock,0,&tIds[numCon]);
			printf("new client");
			numCon++;
			printf("%d num client total!!",numCon);
		}
		return 0;
	}

	int StopAccept()
	{
		acceptFlag = 0;
	}

private:
	SOCKET rawSocket;
	SOCKADDR_IN addr;

	CHAR *buffer;
	static const int MAX_CON = 10;
	SOCKET clientList[MAX_CON];
	int numCon;

	int acceptFlag;

	HANDLE hThreads[10];//线程
	DWORD tIds[10];//线程id

	int initSock()
	{
		addr.sin_family = AF_INET;
		addr.sin_port = htons(4444);
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");

		return bind(rawSocket,(SOCKADDR*)&addr,sizeof(addr));
	}
};

RCPServer *login;

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	;
	if(WSAStartup(MAKEWORD(2,2),&wsaData) !=0 )
	{
		printf("startup error \n");
		return -1;
	}
	 login = new RCPServer();
	 login->Listen();
	 login->StartAccept();
	return 0;
}

int init()
{
	SQLHENV hEnv = NULL;
	SQLHDBC hDbc = NULL;
	SQLHSTMT hStmt = NULL;
	WCHAR *szDNS = (WCHAR *)"PswGame_DB";
	WCHAR *userName = (WCHAR *)"root";
	WCHAR *password = (WCHAR *)"root";

	CHAR  wszInput[SQL_QUERY_SIZE]; 

	if(SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&hEnv) == SQL_ERROR)
	{
		fwprintf(stderr,L"Unable to allocate an environment handle\n");
		return -1;
	}
	
	if(SQLSetEnvAttr(hEnv,SQL_ATTR_ODBC_VERSION,(SQLPOINTER)SQL_OV_ODBC3,0) == SQL_ERROR)
	{
		fwprintf(stderr,L"Unable to Register!\n");
		return -1;
	}
	if(SQLAllocHandle(SQL_HANDLE_DBC,hEnv,&hDbc) == SQL_ERROR)
	{
		fwprintf(stderr,L"Unable to Allocate a connection !\n");
		return -1;
	}
	//if(SQLDriverConnect(hDbc,GetDesktopWindow(),) == SQL_ERROR)
	//if(SQLConnect(hDbc,(SQLWCHAR*)szDNS,SQL_NTS,(SQLWCHAR*)userName,SQL_NTS,(SQLWCHAR*)password,SQL_NTS) == SQL_ERROR)
	SQLRETURN  ret;
	//通过ODBC编程时，不要用UNICODE字符集。在vs2005编程时，需要在项目属性中设置字符集为未设置。
	//然后把你代码中所有出现SQLWCHAR的地方改成SWLCHAR就行了


	ret = SQLConnect(hDbc,(SQLCHAR*)szDNS,SQL_NTS,(SQLCHAR*)userName,SQL_NTS,(SQLCHAR*)password,SQL_NTS);
	
	if(ret == SQL_ERROR)
	{
		fwprintf(stderr,L"Unable to Connect!\n");
		return -1;
	}
	/*
CREATE TABLE IF NOT EXISTS `users` (    
`id` int(9) NOT NULL AUTO_INCREMENT,    
`password` varchar(64) NOT NULL,    
PRIMARY KEY (`id`)    
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=1 ; 

INSERT INTO users (id,password) VALUES (50829,"abcde") ;

SELECT * FROM USERS WHERE id = 50829;
*/
	
	if(SQLAllocHandle(SQL_HANDLE_STMT,hDbc,&hStmt) == SQL_ERROR)
	{
		fwprintf(stderr,L"Unable to Allocate a stmt !\n");
		return -1;
	}

	ret = SQLExecDirect(hStmt,(SQLCHAR*) "SELECT id FROM users WHERE id = 50529",SQL_NTS);

	switch (ret)
	{
	case SQL_SUCCESS_WITH_INFO:
		fwprintf(stderr,L"SQL_SUCCESS_WITH_INFO\n");
		break;
	case SQL_SUCCESS:
		fwprintf(stderr,L"SQL_SUCCESS\n");
		break;
	case SQL_ERROR:
		fwprintf(stderr,L"SQL_ERROR\n");
		break;
	default:
		fwprintf(stderr, L"Unexpected return code %hd!\n", ret); 
		break;
	}

	if(hStmt)
	{
		SQLFreeHandle(SQL_HANDLE_STMT,hStmt);
	}

	if(hDbc)
	{
		SQLDisconnect(hDbc);
		SQLFreeHandle(SQL_HANDLE_DBC,hDbc);
	}

	if(hEnv)
	{
		SQLFreeHandle(SQL_HANDLE_ENV,hEnv);
	}
	//_fgetts(wszInput, SQL_QUERY_SIZE-1, stdin);
	return 0;  
}


DWORD WINAPI ReceProc(LPVOID params)
{
	printf("new thread!");
	SOCKET client = (SOCKET)params;
	
	int RECE_BUFF_SIZE = 8192;
	
	LPVOID recevBuff = HeapAlloc(GetProcessHeap(),0,RECE_BUFF_SIZE);
	LPVOID longBuff = HeapAlloc(GetProcessHeap(),0,RECE_BUFF_SIZE);
	int len = 0;
	int lenRecved;
	do
	{
		lenRecved = recv(client,(char*)recevBuff,RECE_BUFF_SIZE,0);
		memcpy(longBuff,recevBuff,lenRecved);
		len+=lenRecved;
		longBuff = (char*)longBuff+len;
		char mLen[4];
		memcpy(mLen,recevBuff,4);
		UINT *l = (UINT*)(mLen);
		UINT x = *l;
		if(len>=18)
		{
			printf("mLen:%u\n", ntohl(x));
			printf("mLen:%u\n", x);
		}
		
		printf("%dbytes recevied!",lenRecved);
	}while(lenRecved>0);

	
	return 0;
}