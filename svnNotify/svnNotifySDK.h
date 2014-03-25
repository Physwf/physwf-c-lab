#define	WM_ICON_NOTIFY WM_APP+10
// #define _countof(array) (sizeof(array)/sizeof(array[0]))
#define WM_SOCK_RECV WM_APP+100

#ifndef _WIN32_WINNT            // 指定要求的最低平台是 Windows Vista。
#define _WIN32_WINNT 0x0501     // 将此值更改为相应的值，以适用于 Windows 的其他版本。
#endif

/**
线程参数结构
**/
typedef struct my_arg
{
	SOCKET socket;
	int  isOver;
	// HWND hwnd;
} *MY_ARG;
/**
监视线程函数 
**/
DWORD WINAPI DirMonitor(LPVOID param);
/**
接收线程函数
**/
DWORD WINAPI RecvProc(LPVOID param);
/**
建立socket
**/
SOCKET EstablishSocket(void);
