#include "Application.h"
#include "Object3D.h"
#include "Primitives.h"

using namespace Toy3D;

Application::Application()
{
	bExit = false;
}

Application::~Application()
{

}

bool Application::Initialize()
{
	int screenW = 0, screenH = 0;
	InitialzeWindows(screenW, screenH);

	d3dContext = std::make_shared<D3DContext>();
	d3dContext->Initialize(m_hwnd, screenW, screenH,!FULLSCREEN);

	m_spInput = std::make_shared<Input>();
	m_spInput->Initialize();

	m_spScene = std::make_shared<Scene>();
	m_spScene->Initialize(screenW, screenH);

	using Toy3D::Primitives::Line;
	using Toy3D::Primitives::Triangle;
	std::shared_ptr<Line> line = std::make_shared<Line>(D3DXVECTOR3(-10, 0, 0), D3DXVECTOR3(10, 0, 0), D3DCOLOR_XRGB(0, 0, 255));
	std::shared_ptr<Triangle> tri = std::make_shared<Triangle>(D3DXVECTOR3(-20, 10, 0), D3DXVECTOR3(20, 10, 0), D3DXVECTOR3(0, -10, 0), D3DCOLOR_XRGB(255, 0, 0));
	line->SetPosition(0, 0, 100.0f);
	tri->SetPosition(0, 0, 150.0f);
	m_spScene->AddObject(line);
	m_spScene->AddObject(tri);
	return true;
}

void Application::Shutdown()
{
	if (m_spScene)
	{
		m_spScene->Dispose();
	}

	ShutdownWindows();
}

void Application::Run()
{
	MSG msg;
	bool done, result = true;

	ZeroMemory(&msg, sizeof MSG);
	done = false;

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
		else
		{
			result = bExit;

			Frame();
			if (result)
			{
				done = true;
			}
		}
		Sleep(10);
	}

}

bool Application::Frame()
{
	if (m_spInput->IsKeyDown(VK_ESCAPE))
	{
		bExit = true;
		return false;
	}
	m_spScene->Update(0);
	m_spScene->Render();
	return true;
}

void Application::InitialzeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;

	ApplicationHandle = this;

	m_hInstance = GetModuleHandle(NULL);
	m_ApplicationName = "Engine";

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbWndExtra = 0;
	wc.cbClsExtra = 0;
	wc.hInstance = m_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_ApplicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	RegisterClassEx(&wc);

	screenHeight = GetSystemMetrics(SM_CXSCREEN);
	screenWidth = GetSystemMetrics(SM_CXSCREEN);

	if (FULLSCREEN)
	{
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof dmScreenSettings;
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenWidth;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);
		posX = posY = 0;
	}
	else
	{
		screenWidth = 800;
		screenHeight = 600;

		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	if (FULLSCREEN)
	{
		m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_ApplicationName, m_ApplicationName, WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_POPUP, posX, posY, screenWidth, screenHeight, NULL, NULL, m_hInstance, NULL);
	}
	else
	{
		m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_ApplicationName, m_ApplicationName, WS_OVERLAPPEDWINDOW, posX, posY, screenWidth, screenHeight, NULL, NULL, m_hInstance, NULL);
	}

	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);
	//ShowCursor(false);
}

void Application::ShutdownWindows()
{
	//ShowCursor(true);
	if (FULLSCREEN)
		ChangeDisplaySettings(NULL, 0);
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;
	ApplicationHandle = NULL;
}

LRESULT CALLBACK Application::MessageHandler(HWND hwnd, UINT umsg, WPARAM wParam, LPARAM lParam)
{
	switch (umsg)
	{
	case WM_KEYDOWN:
	{
					   m_spInput->KeyDown(static_cast<unsigned int>(wParam));
					   return 0;
	}
	case WM_KEYUP:
	{
					 m_spInput->KeyUp(static_cast<unsigned int>(wParam));
					 return 0;
	}
	default:
	{
			   return DefWindowProc(hwnd, umsg, wParam, lParam);
	}
	}
}

LRESULT CALLBACK Toy3D::WndProc(HWND hwnd, UINT umessage, WPARAM wParam, LPARAM lParam)
{
	switch (umessage)
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
			   return ApplicationHandle->MessageHandler(hwnd, umessage, wParam, lParam);
	}
	}
}