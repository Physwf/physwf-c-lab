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

long appTime;
float FPS;
int interval;
bool inited;

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wPara,LPARAM lPara);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	FPS = 1.0/60.0;
	interval = 1000.0 * FPS;
	inited = false;
	appTime = GetTickCount();
	
	AllocConsole();
	freopen("CONOUT$","w+t",stdout);
	freopen("CONIN$","r+t",stdin);

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
	hwnd = CreateWindowW(L"Hello,World",L"Hello,World",WS_OVERLAPPEDWINDOW|WS_VISIBLE,0,0,VIEW_W,VIEW_H,0,0,hInstance,0);
	
	
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
	printf("interval:%d\n",interval);
	
	while(true)
	{
		int elapse = GetTickCount() - appTime;
		if(elapse >= interval)
		{
			appTime += elapse;
			if(initialized)
			{
				display();
				update(appTime);
				SwapBuffers(ourWindowHandleToDeviceContext);
			}
		}
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE) > 0)
			DispatchMessage(&msg);
	}
	FreeConsole();
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wPara,LPARAM lPara)
{
	switch(msg)
	{
		case WM_CREATE:
			{
				// PIXELFORMATDESCRIPTOR pfd =
				// {
					// sizeof(PIXELFORMATDESCRIPTOR),
					// 1,
					// PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
					// PFD_TYPE_RGBA,
					// 32,
					// 0,0,0,0,0,0,
					// 0,
					// 0,
					// 0,
					// 0,0,0,0,
					// 24,
					// 8,
					// 0,
					// PFD_MAIN_PLANE,
					// 0,
					// 0,0,0
				// };
				// HDC ourWindowHandleToDeviceContext = GetDC(hWnd);
				
				// int letWindowChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext,&pfd);
				// SetPixelFormat(ourWindowHandleToDeviceContext,letWindowChooseThisPixelFormat,&pfd);
				
				// HGLRC ourOpenGLRenderingContext = wglCreateContext(ourWindowHandleToDeviceContext);
				// wglMakeCurrent(ourWindowHandleToDeviceContext,ourOpenGLRenderingContext);
				
				// printf("opengl version: %s\n",glGetString(GL_VERSION));
				
				// initView();
				// initData();
				// initialized = true;
			}
			break;
		case WM_KEYDOWN:
			switch(wPara)
			{
				case VK_LEFT:
					// MessageBoxA(0,"LEFT","KEY DOWN",MB_OK);
					onKeyBoardEvent(100,0,0);
					break;
				case VK_UP:
					// MessageBoxA(0,"UP","KEY DOWN",MB_OK);
					onKeyBoardEvent(101,0,0);
					break;
				case VK_RIGHT:
					// MessageBoxA(0,"RIGHT","KEY DOWN",MB_OK);
					onKeyBoardEvent(102,0,0);
					break;
				case VK_DOWN:
					// MessageBoxA(0,"DOWN","KEY DOWN",MB_OK);
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
