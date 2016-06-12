//#ifndef _APPLICATION_H_
//#define _APPLICATION_H_
#pragma once
#include "Resource.h"
#include <d3d8.h>
#include <d3dx8.h>
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
	virtual HRESULT Frame() { return S_OK; }
	virtual HRESULT ShutDown();
protected:
	virtual HRESULT OneTimeSceneInit() { return S_OK; }
	virtual HRESULT InitDeviceObjects() { return S_OK; };
	virtual HRESULT RestoreDeviceObjects() { return S_OK; }
	virtual HRESULT DeleteDeviceObjects() { return S_OK; }
	virtual HRESULT Render() { return S_OK; }
	virtual HRESULT FrameMove(FLOAT) { return S_OK; }
	virtual HRESULT FinalCleanup() { return S_OK; }

	
	virtual HRESULT CreateVSFromBinFile(IDirect3DDevice8* device, DWORD* dwDecl, TCHAR* strVSPath, DWORD* m_dwVS);

	virtual HRESULT CreateSphereMesh(LPDIRECT3DDEVICE8 pDevice,LPD3DXMESH* ppSphere);
	virtual LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
private:
	BOOL InitInstance(HINSTANCE, int);
	ATOM MyRegisterClass(HINSTANCE);
	
	static CD3DApplication* Instance;
protected:


	HWND m_hWnd{ nullptr };
	int m_iWidth;
	int m_iHeight;
	bool m_bWindowed{ true };
private:
	HINSTANCE m_hInst{ nullptr };
	TCHAR m_szTitle[MAX_LOADSTRING];
	TCHAR m_szWindowClass[MAX_LOADSTRING];
};

static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//#endif