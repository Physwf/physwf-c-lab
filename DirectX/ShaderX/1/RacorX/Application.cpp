#include "Application.h"

CD3DApplication::CD3DApplication()
{
	Instance = (this);
}

CD3DApplication::~CD3DApplication()
{

}

HRESULT CD3DApplication::Initialze(HINSTANCE hInstance, int nCmdShow)
{
	LoadString(hInstance, IDS_APP_TITLE, m_szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_RACORX, m_szWindowClass, MAX_LOADSTRING);
	m_hInst = hInstance;
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow))
	{
		return S_FALSE;
	}
	return S_OK;
}

BOOL CD3DApplication::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hwnd = CreateWindow(m_szWindowClass, m_szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	if (!hwnd)
	{
		DWORD error = GetLastError();
		return FALSE;
	}
	m_hWnd = hwnd;
	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	return TRUE;
}

ATOM CD3DApplication::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RACORX));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_RACORX);
	wcex.lpszClassName = m_szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

LRESULT CD3DApplication::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		//m_spInput->KeyDown(static_cast<unsigned int>(wParam));
		return 0;
		break;
	case WM_KEYUP:
		return 0;
		break;
	default:
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	default:
	{
		return CD3DApplication::Instance->MessageHandler(hWnd, msg, wParam, lParam);
	}
	}
}

CD3DApplication* CD3DApplication::Instance = nullptr;

HRESULT CD3DApplication::Run()
{
	MSG msg;
	bool done = false, result = true;

	HACCEL hAccelTable;
	ZeroMemory(&msg, sizeof MSG);

	hAccelTable = LoadAccelerators(m_hInst, MAKEINTRESOURCE(IDC_RACORX));

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		Sleep(10);
	}
	return S_OK;
}

HRESULT CD3DApplication::ShutDown()
{
	DestroyWindow(m_hWnd);
	m_hWnd = NULL;
	m_hInst = NULL;
	return S_OK;
}
