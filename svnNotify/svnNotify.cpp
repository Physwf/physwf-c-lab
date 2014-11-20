#include "targetver.h"
#include <windows.h>
#include <Wincon.h>

#include <Shellapi.h>
#include <tchar.h>
#include <stdlib.h>
#include <stdio.h>

#include "resource.h"
#include "svnNotifySDK.h"



LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);

LRESULT OnTrayNotification(HWND hwnd,WPARAM wParam,LPARAM lParam);

DWORD CheakExist(void);

char szClassName[] = "SVNNotify";

SOCKET s = NULL;

MY_ARG arg;

HANDLE  hThread[2];

int WINAPI WinMain(HINSTANCE hThisInstance,//程序当前实例的句柄，以后随时可以用GetModuleHandle(0)来获得  
					HINSTANCE hPrevInstance, //这个参数在Win32环境下总是0，已经废弃不用了 
					LPSTR lpszArgument,
					int nFunsterStil)
{
	if(CheakExist()) return 0;
	
	HWND hwnd;
	MSG messages;
	WNDCLASSEX wincl;
	
	wincl.hInstance = hThisInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindowProcedure;
	wincl.style = CS_DBLCLKS;
	wincl.cbSize = sizeof(WNDCLASSEX);
	
	wincl.hIcon = LoadIcon(hThisInstance,MAKEINTRESOURCE(IDI_SVNNOTIFY_ON));
	wincl.hIconSm = LoadIcon(hThisInstance,MAKEINTRESOURCE(IDI_SVNNOTIFY_ON));
	wincl.hCursor = LoadCursor(NULL,IDC_ARROW);
	wincl.lpszMenuName = NULL;
	wincl.cbClsExtra = 0;
	wincl.cbWndExtra = 0;
	
	wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;
	
	if(!RegisterClassEx(&wincl))
	{
		return 0;
	}
	// AllocConsole();
	// freopen("conin$", "r+t", stdin);   
	// freopen("conout$", "w+t", stdout);   
	// freopen("conout$", "w+t", stderr);
	hwnd = CreateWindowEx(
							0,
							szClassName,
							"SVNNotify",
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							544,377,
							HWND_DESKTOP,
							NULL,
							hThisInstance,
							NULL);
	NOTIFYICONDATA nData;
	nData.cbSize = sizeof(NOTIFYICONDATA);
	nData.hWnd = hwnd;
	nData.uID =IDR_POPUP_MENU;
	nData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	nData.uCallbackMessage = WM_ICON_NOTIFY;
	nData.hIcon = LoadIcon(hThisInstance,MAKEINTRESOURCE(IDI_SVNNOTIFY_ON));
	strncpy(nData.szTip, "Hi,there!", _countof(nData.szTip));
	nData.uTimeout = 3000;
	//建立Socket，建立线程
	s = EstablishSocket();
	arg = (MY_ARG) HeapAlloc(GetProcessHeap(),0,sizeof(MY_ARG));
	arg->socket = s;
	(arg->isOver) = 0;
	// arg->hwnd = hwnd;
	DWORD tId[2];

	//建立线程
	if(s !=INVALID_SOCKET)
	{
		hThread[0] = CreateThread(NULL,0,DirMonitor,(LPVOID) arg,0,&tId[0]);
		hThread[1] = CreateThread(NULL,0,RecvProc,(LPVOID) arg,0,&tId[1]);
	}

	
	if(!Shell_NotifyIcon(NIM_ADD,&nData)) 
	{
		return 0;
	}
	
	ShowWindow(hwnd,SW_HIDE);
	
	while(GetMessage(&messages,NULL,0,0))
	{
		TranslateMessage(&messages);
		DispatchMessage(&messages);
	}
	WaitForMultipleObjects(2,hThread,TRUE,INFINITE);
	return messages.wParam;

}

LRESULT WINAPI WindowProcedure(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	int wmId ,wmEvent;
	NOTIFYICONDATA nData;
	char name[60];
	TCHAR dst[30];
	nData.cbSize = sizeof(nData);
	nData.hWnd = hwnd;
	nData.uID = IDR_POPUP_MENU;
	nData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_INFO; 
	nData.uFlags |= NIF_INFO;
	nData.uCallbackMessage = WM_ICON_NOTIFY;
	nData.hIcon = LoadIcon(GetModuleHandle(0),MAKEINTRESOURCE(IDI_SVNNOTIFY_ON));
	nData.dwInfoFlags = NIIF_NONE;  
	char *recvInfo;
	switch(message)
	{
		case WM_DESTROY :
			break;
		case WM_CLOSE:
			PostQuitMessage(WM_QUIT);
			nData.cbSize = sizeof(NOTIFYICONDATA);
			nData.hWnd = hwnd;
			nData.uID =IDR_POPUP_MENU;
			Shell_NotifyIcon(NIM_DELETE,&nData);
			break;
		case WM_ICON_NOTIFY:
			OnTrayNotification(hwnd,wParam,lParam);
			break;
		case WM_COMMAND:
			wmId = LOWORD(wParam);
			wmEvent = HIWORD(wParam);
			
			switch(wmId)
			{
				case IDM_EXIT:
					PostQuitMessage(WM_QUIT);
					(arg->isOver) = 1;
					closesocket(s);
					TerminateThread(hThread[0],1);
					WSACleanup();
					printf("over %d\n",arg->isOver);
					Shell_NotifyIcon(NIM_DELETE,&nData);
					break;
				case IDM_HIDE:
					// strncpy(nData.szTip, "Hi,there!", _countof(nData.szTip));
					// lstrcpy(nData.szInfoTitle, TEXT("提醒"));
					// lstrcpy(name, (char *) lParam);
					// sprintf(dst,_T("%s"),(TCHAR *) lParam);
					// lstrcpy(nData.szInfo, TEXT("XXX提交了更新"));
					// lstrcpy(nData.szInfo, dst);
					// printf(nData.szInfoTitle);
					// printf(nData.szInfo);
					// nData.uTimeout = 5000;
					// printf("hi %d\n",Shell_NotifyIcon(NIM_MODIFY,&nData));
					ShowWindow(hwnd,SW_HIDE);
					break;
			}
			break;
		case WM_COPYDATA:
			// data = (PCOPYDATASTRUCT) lParam;
			// _tcsncpy(nData.szInfo, (TCHAR *) data->lpData, 256);
			break;
		case WM_SOCK_RECV:
			strncpy(nData.szTip, "Hi,there!", _countof(nData.szTip));
			lstrcpy(nData.szInfoTitle, TEXT("提醒"));
			// lstrcpy(name, (char *) lParam);
			sprintf(dst,_T("%s%s"),(TCHAR *) lParam,"提交了更新！");
			// lstrcpy(nData.szInfo, TEXT("XXX提交了更新"));
			lstrcpy(nData.szInfo, dst);
			printf(nData.szInfoTitle);
			printf(nData.szInfo);
			nData.uTimeout = 5000;
			printf("hi %d\n",Shell_NotifyIcon(NIM_MODIFY,&nData));
			break;
		default :
			//其他消息交给由系统提供的缺省处理函数
			return DefWindowProc(hwnd,message,wParam,lParam);
			break;
	}
	return 0;
}

LRESULT OnTrayNotification(HWND hwnd,WPARAM wParam,LPARAM lParam)
{

	if(LOWORD(lParam) == WM_RBUTTONUP)
	{
		POINT pos;
		GetCursorPos(&pos);
		HINSTANCE hTargetWnd = GetModuleHandle(0);
		HMENU hmenu = LoadMenu(hTargetWnd,MAKEINTRESOURCE(IDR_POPUP_MENU));
		if(!hmenu) return 0;
		HMENU hSubMenu = GetSubMenu(hmenu, 0);
		if(!hSubMenu) return 0;
		SetForegroundWindow(hwnd);
		TrackPopupMenu(hSubMenu,TPM_RIGHTALIGN | TPM_BOTTOMALIGN,pos.x,pos.y,0,hwnd,NULL);
		DestroyMenu(hmenu);
	}
	return 1;
}

DWORD CheakExist(void)
{
	HANDLE hMutex = CreateMutex(NULL,FALSE,"SVNNotify");
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hMutex);
		return 1;
	}
	return 0;
}