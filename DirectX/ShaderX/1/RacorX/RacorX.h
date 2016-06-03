#pragma once

#include "Application.h"
#include <d3d8.h>
#include <d3dx8.h>
#include <memory>

struct Vertex
{
	float x; float y; float z;
	static const DWORD FVF;
};


class CRacorX : public CD3DApplication
{
public:
	CRacorX();
	~CRacorX();

	virtual HRESULT Frame();
protected:
	virtual HRESULT ConfirmDevice(D3DCAPS8* pCaps, DWORD dwBehavior, D3DFORMAT Format);
	virtual HRESULT OneTimeSceneInit();
	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT Render();
	virtual HRESULT FrameMove(FLOAT);
	virtual HRESULT FinalCleanup();

private:
	std::shared_ptr<IDirect3D8> m_spD3D{ nullptr };
	std::shared_ptr<IDirect3DDevice8> m_spDevice{ nullptr };
	D3DCAPS8 m_D3DCAPS;
	D3DPRESENT_PARAMETERS m_dpps;
	int m_iVP;
	D3DVIEWPORT8 m_Viewport;

	std::shared_ptr<IDirect3DVertexBuffer8> m_spVB;
	std::shared_ptr<IDirect3DIndexBuffer8> m_spIB;
	
	DWORD m_dwVertexShader;
	Vertex m_Vertices[4];

	D3DXMATRIX m_mtWorld;
	D3DXMATRIX m_mtView;
	D3DXMATRIX m_mtProj;

	float m_fMaterial[4];
	
};


