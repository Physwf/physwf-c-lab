#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

#pragma comment (lib,"kernel32.lib")
#pragma comment (lib,"user32.lib")

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wPara,LPARAM lPara);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg 		= {0};
	WNDCLASSEX wc	= {0};
	wc.cbSize 		= sizeof(WNDCLASSEX);
	wc.lpfnWndProc 	= WndProc;
	wc.hInstance 	= GetModuleHandle(NULL);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	wc.lpszClassName = "Hello,world";
	wc.style = CS_OWNDC;
	wc.hCursor		= LoadCursor(NULL,IDC_ARROW);
	wc.hIcon		= LoadIconW(wc.hInstance,MAKEINTRESOURCEW(IDI_APPLICATION));
	wc.hIconSm		= LoadIconW(wc.hInstance,MAKEINTRESOURCEW(IDI_APPLICATION));
	if(!RegisterClassEx(&wc))
		return 1;
	CreateWindowW(L"Hello,World",L"Hello,World",WS_OVERLAPPEDWINDOW|WS_VISIBLE,0,0,640,480,0,0,hInstance,0);
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
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd,msg,wPara,lPara);
			break;
	}
	return 0;
}