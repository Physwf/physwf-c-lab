#define	WM_ICON_NOTIFY WM_APP+10
// #define _countof(array) (sizeof(array)/sizeof(array[0]))
#define WM_SOCK_RECV WM_APP+100

#ifndef _WIN32_WINNT            // ָ��Ҫ������ƽ̨�� Windows Vista��
#define _WIN32_WINNT 0x0501     // ����ֵ����Ϊ��Ӧ��ֵ���������� Windows �������汾��
#endif

/**
�̲߳����ṹ
**/
typedef struct my_arg
{
	SOCKET socket;
	int  isOver;
	// HWND hwnd;
} *MY_ARG;
/**
�����̺߳��� 
**/
DWORD WINAPI DirMonitor(LPVOID param);
/**
�����̺߳���
**/
DWORD WINAPI RecvProc(LPVOID param);
/**
����socket
**/
SOCKET EstablishSocket(void);
