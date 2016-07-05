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
	virtual HRESULT CreatePSFromBinFile(IDirect3DDevice8* device, TCHAR* strVSPath, DWORD* m_dwPS);

	virtual HRESULT CreateSphereMesh(LPDIRECT3DDEVICE8 pDevice,LPD3DXMESH* ppSphere);
	virtual HRESULT CreatePlane(LPDIRECT3DDEVICE8 pDevice, float fSize, WORD strip, LPD3DXMESH* ppSphere);
	template<typename T1, typename T2> HRESULT CreateNormal(IDirect3DVertexBuffer8* vbIn, IDirect3DVertexBuffer8* vbOut);
	template<typename T1, typename T2> HRESULT CreateTangent(IDirect3DVertexBuffer8* vbIn, IDirect3DVertexBuffer8* vbOut);
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

template<typename T1, typename T2> HRESULT CD3DApplication::CreateNormal(IDirect3DVertexBuffer8* pvbIn, IDirect3DVertexBuffer8* pvbOut)
{
	D3DVERTEXBUFFER_DESC descIn,descOut;
	pvbIn->GetDesc(&descIn);
	pvbOut->GetDesc(&descOut);
	T1* vertexIn;
	T2* vertexOut;
	if (SUCCEEDED(pvbIn->Lock(0, descIn.Size, reinterpret_cast<BYTE**>(&vertexIn), 0)))
	{
		DWORD numVerticesIn = descIn.Size / (sizeof T1);
		if (SUCCEEDED(pvbOut->Lock(0, descOut.Size, reinterpret_cast<BYTE**>(&vertexOut), 0)))
		{
			for (DWORD i = 0; i < numVerticesIn; ++i)
			{
				vertexOut->x = vertexIn->x;
				vertexOut->y = vertexIn->y;
				vertexOut->z = vertexIn->z;
				++vertexOut;
				vertexOut->x = vertexIn->x + vertexIn->nx *  0.3f;
				vertexOut->y = vertexIn->y + vertexIn->ny *  0.3f;
				vertexOut->z = vertexIn->z + vertexIn->nz *  0.3f;
				++vertexOut;

				++vertexIn;
			}
			pvbOut->Unlock();
		}
		pvbIn->Unlock();
	}
	return S_OK;
}

template<typename T1, typename T2> HRESULT CD3DApplication::CreateTangent(IDirect3DVertexBuffer8* pvbIn, IDirect3DVertexBuffer8* pvbOut)
{
	D3DVERTEXBUFFER_DESC descIn, descOut;
	pvbIn->GetDesc(&descIn);
	pvbOut->GetDesc(&descOut);
	T1* vertexIn;
	T2* vertexOut;
	if (SUCCEEDED(pvbIn->Lock(0, descIn.Size, reinterpret_cast<BYTE**>(&vertexIn), 0)))
	{
		DWORD numVerticesIn = descIn.Size / (sizeof T1);
		if (SUCCEEDED(pvbOut->Lock(0, descOut.Size, reinterpret_cast<BYTE**>(&vertexOut), 0)))
		{
			for (DWORD i = 0; i < numVerticesIn; ++i)
			{
				vertexOut->x = vertexIn->x;
				vertexOut->y = vertexIn->y;
				vertexOut->z = vertexIn->z;
				++vertexOut;
				vertexOut->x = vertexIn->x + vertexIn->bx * 0.3f;
				vertexOut->y = vertexIn->y + vertexIn->by * 0.3f;
				vertexOut->z = vertexIn->z + vertexIn->bz * 0.3f;
				++vertexOut;

				++vertexIn;
			}
			pvbOut->Unlock();
		}
		pvbIn->Unlock();
	}
	return S_OK;
}
//#endif