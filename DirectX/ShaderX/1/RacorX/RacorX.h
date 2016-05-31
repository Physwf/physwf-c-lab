#pragma once

#include "Resource.h"
//#include <d3d8.h>
#include <windows.h>
#include <memory>

#define MAX_LOADSTRING 100

class CD3DApplication
{
public:
	friend LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:
	CD3DApplication();
	~CD3DApplication();

	virtual HRESULT Initialze(HINSTANCE hInstance, int nCmdShow);
	virtual HRESULT Run();
	virtual HRESULT ShutDown();

	//virtual HRESULT ConfirmDevice(D3DCAPS8*);
	//virtual HRESULT OneTimeSceneInit();
	//virtual HRESULT InitDeviceObjects();
	//virtual HRESULT RestoreDeviceObjects();
	//virtual HRESULT DeleteDeviceObjects();
	//virtual HRESULT Render();
	//virtual HRESULT FrameMove(FLOAT);
	//virtual HRESULT FinalCleanup();
private:
	BOOL InitInstance(HINSTANCE, int);
	ATOM MyRegisterClass(HINSTANCE);
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
	static std::shared_ptr<CD3DApplication> Instance;
private:
	HINSTANCE m_hInst{ nullptr };
	HWND m_hWnd{ nullptr };
	TCHAR m_szTitle[MAX_LOADSTRING];
	TCHAR m_szWindowClass[MAX_LOADSTRING];
};

static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);