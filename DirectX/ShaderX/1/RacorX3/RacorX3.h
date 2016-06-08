#pragma once

#include "Application.h"
#include <memory>

struct Vertex
{
	float x; float y; float z;
	float nx; float ny; float nz;
	static const DWORD FVF;
};

class RacorX3 : public CD3DApplication 
{
public:
	RacorX3();
	~RacorX3();

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
	std::shared_ptr<IDirect3D8> m_spD3D;
	std::shared_ptr<IDirect3DDevice8> m_spDevice;
	D3DCAPS8 m_D3DCaps;
	D3DPRESENT_PARAMETERS m_dpps;
	int m_iVP;
	D3DVIEWPORT8 m_Viewport;

	std::shared_ptr<IDirect3DVertexBuffer8> m_spVB;
	std::shared_ptr<IDirect3DIndexBuffer8> m_spIB;

	DWORD m_dwVSH;

	D3DXMATRIX m_mtWorld;
	D3DXMATRIX m_mtView;
	D3DXMATRIX m_mtProj;

};