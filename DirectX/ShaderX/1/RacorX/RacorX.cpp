#include "RacorX.h"

CRacorX::CRacorX(HWND hwnd, int width, int height)
{
	m_hWnd = hwnd;
	m_iWidth = width;
	m_iHeight = height;
}

HRESULT CRacorX::ConfirmDevice(D3DCAPS8* pCaps, DWORD dwBehavior, D3DFORMAT Format)
{
	if ((dwBehavior & D3DCREATE_HARDWARE_VERTEXPROCESSING) || (dwBehavior & D3DCREATE_MIXED_VERTEXPROCESSING))
	{
		if (pCaps->VertexShaderVersion < D3DVS_VERSION(1, 1))
			return E_FAIL;
	}
	return S_OK;
}

HRESULT CRacorX::OneTimeSceneInit()
{
	IDirect3D8* d3d = Direct3DCreate8(D3D_SDK_VERSION);
	m_spD3D.reset(d3d, [](IDirect3D8* d3d) { d3d->Release(); });
	m_spD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3DCAPS);
}

HRESULT CRacorX::InitDeviceObjects()
{
	int vp = 0;
	if (m_D3DCAPS.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth = m_iWidth;
	d3dpp.BackBufferHeight = m_iHeight;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	//d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = m_hWnd;
	d3dpp.Windowed = m_bWindowed;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.FullScreen_PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	IDirect3DDevice8* device;
	HRESULT result = m_spD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_hWnd,
		vp,
		&d3dpp,
		&device
		);
}
