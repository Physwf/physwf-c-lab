//#define UNICODE
#include <windows.h>
#include <stdlib.h>
#include <string.h>
//#include <tchar.h>

#pragma comment (lib,"kernel32.lib")
#pragma comment (lib,"user32.lib")

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wPara,LPARAM lPara);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg 		= {0};
	WNDCLASS wc		= {0};
	wc.lpfnWndProc 	= WndProc;
	wc.hInstance 	= hInstance;
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	wc.lpszClassName = "Hello,world";
	wc.style = CS_OWNDC;
	if(!RegisterClass(&wc))
		return 1;
	CreateWindowW(wc.lpszClassName,L"Hello,world",WS_OVERLAPPEDWINDOW|WS_VISIBLE,0,0,640,480,0,0,hInstance,0);
	while(GetMessage(&msg,NULL,0,0) > 0)
		DispatchMessage(&msg);
	
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wPara,LPARAM lPara)
{
	switch(msg)
	{
		case WM_CREATE:
			break;
		case WM_DESTROY:
			break;
		default:
			return DefWindowProc(hWnd,msg,wPara,lPara);
			break;
	}
	return 0;
}