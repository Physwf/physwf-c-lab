#include "RacorX.h"
#include <d3dx8.h>

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

	DWORD dwDecl0[] = {
		D3DVSD_STREAM(0),
		D3DVSD_REG(0,D3DVSDT_FLOAT3),
		D3DVSD_REG(5,D3DVSDT_D3DCOLOR),
		D3DVSD_CONST(0, 1), *(DWORD*)&m_fDiffuse[0], *(DWORD*)&m_fDiffuse[1], *(DWORD*)&m_fDiffuse[2], *(DWORD*)&m_fDiffuse[3],
		D3DVSD_END()
	};

	IDirect3DVertexBuffer8* vb;
	m_spDevice->CreateVertexBuffer(
		sizeof(m_Vertices),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&vb);
	m_spVB.reset(vb, [](IDirect3DVertexBuffer8* vb){ vb->Release(); });

	m_spVB->Lock(0, 0, reinterpret_cast<BYTE**>(m_Vertices), 0);

	m_Vertices[0] = { 0.0f, 0.0f, 0.0f };
	m_Vertices[1] = { 0.0f, 0.0f, 0.0f };
	m_Vertices[2] = { 0.0f, 0.0f, 0.0f };
	m_Vertices[3] = { 0.0f, 0.0f, 0.0f };

	m_spVB->Unlock();

	IDirect3DIndexBuffer8* ib;
	m_spDevice->CreateIndexBuffer(
		6 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&ib);
	m_spIB.reset(ib, [](IDirect3DIndexBuffer8* ib){ ib->Release(); });

	WORD *indices;
	m_spIB->Lock(0, 0, reinterpret_cast<BYTE**>(indices), 0);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 1;

	m_spIB->Unlock();

	const char vsh[] = 
		"vs.1.1"\
		"dp4 oPos.x, v0, c4"\
		"dp4 oPos.y, v0, c5"\
		"dp4 oPos.z, v0, c6"\
		"dp4 oPos.w, v0, c7"\
		"mov oD0, c8";
	ID3DXBuffer* pVBuffer;
	ID3DXBuffer* pErrors;
	HRESULT rc = D3DXAssembleShader(reinterpret_cast<LPCVOID>(vsh), sizeof(vsh) - 1, 0, NULL, &pVBuffer, &pErrors);
	if (FAILED(rc))
	{
		OutputDebugString(L"Failed to assemble the vertex shader, error:\n");
		OutputDebugString(reinterpret_cast<WCHAR*>(pErrors->GetBufferPointer()));
		OutputDebugString(L"\n");
	}

	rc = m_spDevice->CreateVertexShader(dwDecl0, reinterpret_cast<DWORD*>(pVBuffer->GetBufferPointer()), &m_dwVertexShader, 0);
	if (FAILED(rc))
	{
		OutputDebugString(L"Failed to create vertex shader, error:\n");
		WCHAR szBuffer[512] = { 0 };
		D3DXGetErrorString(rc, szBuffer, sizeof(szBuffer));
		OutputDebugString(szBuffer);
		OutputDebugString(L"\n");
	}
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
