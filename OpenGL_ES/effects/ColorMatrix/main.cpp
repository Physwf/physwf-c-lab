#include <stdio.h>
#include <windows.h>
#include <windowsx.h>

#include "ColorMatrix.h"
#include "ColorMatrixUI.h"

#pragma comment (lib,"kernel32.lib")
#pragma comment (lib,"user32.lib")
#pragma comment (lib,"Gdi32.lib")

CPaintManagerUI m_PaintManager;

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	switch(msg)
	{
		case WM_CREATE:
			{
				m_PaintManager.Init(hWnd);
				CDialogBuilder builder;
				CControlUI* pRoot = builder.Create(_T("Data/ColorMatrixFrame.xml"), (UINT)0, NULL, &m_PaintManager);  
				ASSERT(pRoot && "Failed to parse XML\n");
				if(pRoot) printf("pRoot\n");
				m_PaintManager.AttachDialog(pRoot);
				return 0;
			}
			break;
		case WM_LBUTTONDOWN:
			if(MK_LBUTTON & wParam)
				//onMousePressed(GET_X_LPARAM(lParam),GET_Y_LPARAM(lParam));
			break;
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			// return DefWindowProc(hWnd,msg,wParam,lParam);
			break;
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}

HWND create_window(int w,int h)
{
	HWND window;
	WNDCLASS wc;
	RECT rect;
	HINSTANCE hInstance;
	
	rect.left = 0L;
	rect.right = (long)w;
	rect.top = 0L;
	rect.bottom = (long)h;
	
	hInstance = GetModuleHandle(NULL);
	
	//CPaintManagerUI::SetInstance(hInstance);
	//CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
	//CColorMatrixFrame cmFrame;
	// window = cmFrame.Create(NULL,_T(""),UI_WNDSTYLE_FRAME,WS_EX_WINDOWEDGE);
	//window = cmFrame.Create(NULL,_T("ColorMatrix"),WS_OVERLAPPEDWINDOW|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,WS_EX_APPWINDOW|WS_EX_WINDOWEDGE,rect);
	//cmFrame.ShowModal();
	//cmFrame.ShowWindow(true,true);
	//return window;
	
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Blur";
	
	RegisterClass(&wc);
	
	AdjustWindowRectEx(&rect,WS_OVERLAPPEDWINDOW,FALSE,WS_EX_APPWINDOW|WS_EX_WINDOWEDGE);
	
	window = CreateWindowEx(
	WS_EX_APPWINDOW|WS_EX_WINDOWEDGE,
	"Blur",
	"Blur",
	WS_OVERLAPPEDWINDOW|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
	0,0,
	rect.right - rect.left,
	rect.bottom - rect.top,
	NULL,NULL,
	hInstance,
	NULL );
	
	ShowWindow(window,SW_SHOW);
	SetForegroundWindow(window);
	SetFocus(window);
	
	return window;
}

int lastTick;
const int FPS = 60;
const int interval = 1000/FPS;

int main()
{
	EGLint majorVersion;
	EGLint minorVersion;
	EGLDisplay display;
	
	display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if(display == EGL_NO_DISPLAY)
	{
		printf("Unable to open connection to local windowing system!\n");
	}
	if(!eglInitialize(display,&majorVersion,&minorVersion))
	{
		printf("Unable to initialize EGL!");
	}
	
	EGLint attribList[] = 
	{
		EGL_RENDERABLE_TYPE,EGL_OPENGL_ES2_BIT,
		EGL_RED_SIZE,8,
		EGL_GREEN_SIZE,8,
		EGL_BLUE_SIZE,8,
		EGL_DEPTH_SIZE,16,
		EGL_NONE
	};
	
	const EGLint MaxConfigs = 10;
	EGLConfig configs[MaxConfigs];
	EGLint numConfigs;
	
	if(!eglChooseConfig(display,attribList,configs,MaxConfigs,&numConfigs))
	{
		printf("Choose Config failed!\n");
	}

	HWND window = create_window(VIEW_W,VIEW_H);
	CPaintManagerUI::SetInstance(GetModuleHandle(NULL));
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
	CColorMatrixFrame cmFrame;
	cmFrame.Create(window,_T("ColorMatrix"), UI_WNDSTYLE_CHILD, 0, 0, 0, 500, 400);
	EGLSurface surface;
	surface = eglCreateWindowSurface(display,configs[0],window,NULL);

	if(surface == EGL_NO_SURFACE)
	{
		printf("Surface create error!\n");
	}

	EGLContext context;
	EGLint contextAttribList[] = 
	{
		EGL_CONTEXT_CLIENT_VERSION,2,
		EGL_NONE
	};
	context = eglCreateContext(display,configs[0],EGL_NO_CONTEXT,contextAttribList);

	if(context == EGL_NO_CONTEXT)
	{
		printf("Create context error!\n");
	}
	
	if(!eglMakeCurrent(display,surface,surface,context))
	{
		printf("Make current error!\n");
		
	}

	lastTick = GetTickCount();
	//initData();
	//initView();
	initGray();

	bool done = false;
	MSG msg;
	while(!done)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{
				done = true;
				PostQuitMessage(0);
				break;
			}
			
			{
				::TranslateMessage(&msg);
				::DispatchMessage(&msg);
			}
		}
		int eclipse = GetTickCount() - lastTick;
		
		if(eclipse>=interval)
		{
			update(eclipse);
			lastTick += eclipse;
			render();
			eglSwapBuffers(display,surface);
		}
		Sleep(1);
	}
	return 0;
}
