#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>
#include "TetrisView.h"
#include "TetrisData.h"

#pragma comment (lib,"kernel32.lib")
#pragma comment (lib,"user32.lib")
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"Gdi32.lib")

long lastRenderTime;
long lastUpdateTime;
float FPS;
int renderInterval;
int updateInterval;
bool inited;

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wPara,LPARAM lPara);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	FPS = 1.0/60.0;
	renderInterval = 1000.0 * FPS;
	updateInterval = 800;//ms
	inited = false;
	lastRenderTime = GetTickCount();
	lastUpdateTime = lastRenderTime;
	
	// AllocConsole();
	// freopen("CONOUT$","w+t",stdout);
	// freopen("CONIN$","r+t",stdin);

	HWND hwnd;
	MSG msg 		= {0};
	WNDCLASSEX wc	= {0};
	wc.cbSize 		= sizeof(WNDCLASSEX);
	wc.lpfnWndProc 	= WndProc;
	wc.hInstance 	= GetModuleHandle(NULL);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	wc.lpszClassName = "Hello,world";
	wc.style = CS_OWNDC;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hCursor		= LoadCursor(NULL,IDC_ARROW);
	wc.hIcon		= LoadIconW(NULL,MAKEINTRESOURCEW(IDI_APPLICATION));
	wc.hIconSm		= LoadIconW(NULL,MAKEINTRESOURCEW(IDI_APPLICATION));
	if(!RegisterClassEx(&wc))
		return 1;
	RECT wr = {0,0,VIEW_W,VIEW_H};
	AdjustWindowRect(&wr,WS_OVERLAPPEDWINDOW,false);
	hwnd = CreateWindowW(L"Hello,World",
						L"Hello,World",
						WS_OVERLAPPEDWINDOW|WS_VISIBLE,
						0,0,
						wr.right - wr.left,
						wr.bottom - wr.top,
						0,0,
						hInstance,
						0);
	
	
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0,0,0,0,0,0,
		0,
		0,
		0,
		0,0,0,0,
		24,
		8,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};
	HDC ourWindowHandleToDeviceContext = GetDC(hwnd);
	
	int letWindowChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext,&pfd);
	if(letWindowChooseThisPixelFormat == 0) return 0;
	if(!SetPixelFormat(ourWindowHandleToDeviceContext,letWindowChooseThisPixelFormat,&pfd))
	{
		return 0;
	}
	
	HGLRC ourOpenGLRenderingContext = wglCreateContext(ourWindowHandleToDeviceContext);
	if(!wglMakeCurrent(ourWindowHandleToDeviceContext,ourOpenGLRenderingContext))
	{
		printf("make context failed!\n");
	}
	
	ShowWindow(hwnd, nCmdShow);              //display the window on the screen
	UpdateWindow(hwnd);
	
	printf("opengl version: %s\n",glGetString(GL_VERSION));
	
	initView();
	initData();
	initialized = true;
	printf("renderInterval:%d\n",renderInterval);
	bool done = false;
	while(!done)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		// if(GetMessage(&msg,NULL,0,0))
		{
			if(msg.message == WM_QUIT)
			{
				done = true;
			}
			TranslateMessage(&msg);	
			DispatchMessage(&msg);
		}
		else
		{
			int elapse = GetTickCount() - lastRenderTime;
			if(elapse >= renderInterval)
			{
				lastRenderTime += elapse;
				if(initialized)
				{
					display();
					update(elapse);
					SwapBuffers(ourWindowHandleToDeviceContext);
				}
			}
		}
		Sleep(1);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wPara,LPARAM lPara)
{
	switch(msg)
	{
		case WM_CREATE:
			break;
		case WM_KEYDOWN:
			switch(wPara)
			{
				case VK_LEFT:
					onKeyBoardEvent(100,0,0);
					break;
				case VK_UP:
					onKeyBoardEvent(101,0,0);
					break;
				case VK_RIGHT:
					onKeyBoardEvent(102,0,0);
					break;
				case VK_DOWN:
					onKeyBoardEvent(103,0,0);
					break;
			}
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
