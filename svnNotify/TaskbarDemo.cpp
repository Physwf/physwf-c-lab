/* ************************************
*����ͨWindows API�� 
* ʾ������
* TaskbarDemo.cpp
* 12.4 ֪ͨ����ͼ��
**************************************/
/*  Ԥ����������*/
#include "stdafx.h"
#include "resource.h"
#include "SystemTraySDK.h"

#define MAX_LOADSTRING 100
#define	WM_ICON_NOTIFY WM_APP+10

/*  ȫ�ֱ�����*/
HINSTANCE hInst;								
TCHAR szTitle[MAX_LOADSTRING];					
TCHAR szWindowClass[MAX_LOADSTRING];			
CSystemTray TrayIcon;

/*  ����������*/
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

/* ************************************
* WinMain
* ��ں���
**************************************/
int APIENTRY WinMain(HINSTANCE hInstance,
					 HINSTANCE hPrevInstance,
					 LPSTR     lpCmdLine,
					 int       nCmdShow)
{
	MSG msg;
	HACCEL hAccelTable;

	// �ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TASKBARDEMO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ��ʼ��
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_TASKBARDEMO);
	// ��Ϣѭ��
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

/* ************************************
* ATOM MyRegisterClass(HINSTANCE hInstance)
* ����	ע�ᴰ����
**************************************/
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_TASKBARDEMO);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_TASKBARDEMO;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_TASKBARDEMO);

	return RegisterClassEx(&wcex);
}
/* ************************************
* BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
* ����	�������ں�ͼ��
**************************************/
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; 

	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	// ����֪ͨ����ͼ��
	if (!TrayIcon.Create(hInstance,
		hWnd,																	// ������
		WM_ICON_NOTIFY,											// Notify
		_T("This is a Tray Icon - Right click on me!"),	// tooltip
		::LoadIcon(hInstance, (LPCTSTR)IDI_TASKBARDEMO),
		IDR_POPUP_MENU)) 
		return FALSE;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

/* ************************************
* WndProc
* ����	��������Ϣ����
**************************************/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{

	case WM_ICON_NOTIFY:
		return TrayIcon.OnTrayNotification(wParam, lParam);

	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// �˵�
		switch (wmId)
		{
			// ͼ���Ҽ��˵���ѡ�� Action
		case IDM_ANIMATE:
			// ����
			TrayIcon.SetIconList(IDI_ICON1, IDI_ICON4);
			TrayIcon.Animate(50, 2); 
			// ��ʾ����֪ͨ
			TrayIcon.ShowBalloon("THIS IS A BALLOON",":)",0,10);
			// ��֪ͨ����ָ�ԭʼ��С
			TrayIcon.MaximiseFromTray(hWnd);
			break; 
			// �˳�
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
			// ���أ���С����֪ͨ����
		case IDM_HIDE:
			TrayIcon.MinimiseToTray(hWnd);
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		RECT rt;
		GetClientRect(hWnd, &rt);
		DrawText(hdc, szHello, strlen(szHello), &rt, DT_VCENTER | DT_CENTER | DT_SINGLELINE |DT_WORDBREAK);
		EndPaint(hWnd, &ps);
		break;
		// �˳�
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}