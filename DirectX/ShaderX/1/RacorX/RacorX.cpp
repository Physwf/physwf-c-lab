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

	m_Vertices[0] = { 0.0f, 0.0f, 0.0f };
	m_Vertices[1] = { 0.0f, 0.0f, 0.0f };
	m_Vertices[2] = { 0.0f, 0.0f, 0.0f };
	m_Vertices[3] = { 0.0f, 0.0f, 0.0f };

}

HRESULT CRacorX::InitDeviceObjects()
{
	if (m_D3DCAPS.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
		m_iVP = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	} else {
		m_iVP = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
	D3DPRESENT_PARAMETERS m_dpps;
	m_dpps.BackBufferWidth = m_iWidth;
	m_dpps.BackBufferHeight = m_iHeight;
	m_dpps.BackBufferFormat = D3DFMT_A8R8G8B8;
	m_dpps.BackBufferCount = 1;
	m_dpps.MultiSampleType = D3DMULTISAMPLE_NONE;
	//d3dpp.MultiSampleQuality = 0;
	m_dpps.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_dpps.hDeviceWindow = m_hWnd;
	m_dpps.Windowed = m_bWindowed;
	m_dpps.EnableAutoDepthStencil = true;
	m_dpps.AutoDepthStencilFormat = D3DFMT_D24S8;
	m_dpps.Flags = 0;
	m_dpps.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_dpps.FullScreen_PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	RestoreDeviceObjects();
}

HRESULT CRacorX::RestoreDeviceObjects()
{
	IDirect3DDevice8* device;
	HRESULT result = m_spD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_hWnd,
		m_iVP,
		&m_dpps,
		&device);
	m_spDevice.reset(device, [](IDirect3DDevice8* device){ device->Release(); });
}

HRESULT CRacorX::DeleteDeviceObjects()
{

}

HRESULT CRacorX::Render()
{

}

HRESULT CRacorX::FrameMove(FLOAT)
{

}

HRESULT CRacorX::FinalCleanup()
{

}
