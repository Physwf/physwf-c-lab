#pragma once

#include <d3d8.h>
#include <windows.h>
#include <memory>

struct Vertex
{
	float x; float y; float z;
};
class CRacorX
{
public:
	CRacorX(HWND hwnd, int width, int height);
	~CRacorX();

	virtual HRESULT ConfirmDevice(D3DCAPS8* pCaps, DWORD dwBehavior, D3DFORMAT Format);
	virtual HRESULT OneTimeSceneInit();
	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT Render();
	virtual HRESULT FrameMove(FLOAT);
	virtual HRESULT FinalCleanup();

private:
	HWND m_hWnd;
	int m_iWidth;
	int m_iHeight;
	bool m_bWindowed{ false };
	std::shared_ptr<IDirect3D8> m_spD3D{ nullptr };
	std::shared_ptr<IDirect3DDevice8> m_spDevice{ nullptr };
	D3DCAPS8 m_D3DCAPS;
	D3DPRESENT_PARAMETERS m_dpps;
	int m_iVP;

	Vertex m_Vertices[4];
	float m_Diffuse[3] = { 0.0f, 0.0f, 0.0f};

};


