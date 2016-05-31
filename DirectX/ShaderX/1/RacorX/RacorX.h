#pragma once

#include <d3d8.h>
#include <windows.h>
#include <memory>

class CRacorX
{
public:
	CRacorX();
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
};


