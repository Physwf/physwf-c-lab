//#ifndef _APPLICATION_H_
//#define _APPLICATION_H_
#pragma once
#include "Resource.h"
//#include <d3d8.h>
#include <windows.h>

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

private:
	BOOL InitInstance(HINSTANCE, int);
	ATOM MyRegisterClass(HINSTANCE);
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
	static CD3DApplication* Instance;
private:
	HINSTANCE m_hInst{ nullptr };
	HWND m_hWnd{ nullptr };
	TCHAR m_szTitle[MAX_LOADSTRING];
	TCHAR m_szWindowClass[MAX_LOADSTRING];
};

static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//#endif