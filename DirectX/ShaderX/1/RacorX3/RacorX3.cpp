#include "RacorX3.h"
#include "const.h"
RacorX3::RacorX3()
{

}

RacorX3::~RacorX3()
{

}

HRESULT RacorX3::Frame()
{
	FrameMove(0.0f);
	Render();
	return S_OK;
}

HRESULT RacorX3::ConfirmDevice(D3DCAPS8* pCaps, DWORD dwBehavior, D3DFORMAT Format)
{
	if ((dwBehavior & D3DCREATE_HARDWARE_VERTEXPROCESSING) || (D3DCREATE_MIXED_VERTEXPROCESSING))
	{
		if (pCaps->VertexShaderVersion < D3DVS_VERSION(1, 1))
			return E_FAIL;
	}
	return S_OK;
}

HRESULT RacorX3::OneTimeSceneInit()
{
	IDirect3D8* d3d = Direct3DCreate8(D3D_SDK_VERSION);
	if (d3d == nullptr)
	{
		MessageBox(m_hWnd, L"Direct3DCreate8 failed!", L"Error", 0);
		return E_FAIL;
	}
	m_spD3D.reset(d3d, [](IDirect3D8* d3d) { d3d->Release(); });
	m_spD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3DCaps);

	D3DXMatrixPerspectiveFovLH(&m_mtProj, D3DX_PI*0.5, static_cast<float>(m_iWidth) / m_iHeight, 1.0f, 1000.0f);
	D3DXVECTOR3 pos(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 eye(0.0f, 0.0f, -200.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_mtView, &eye, &pos, &up);
	D3DXMatrixIdentity(&m_mtWorld);

	m_Viewport = { 0, 0, m_iWidth, m_iHeight };

	return S_OK;
}

HRESULT RacorX3::InitDeviceObjects()
{
	HRESULT hr;

	if (m_D3DCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
		m_iVP = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else {
		m_iVP = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
	hr = ConfirmDevice(&m_D3DCaps, m_iVP, D3DFMT_UNKNOWN);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"ConfirmDevice failed!", L"Error", 0);
		return E_FAIL;
	}
	m_dpps.BackBufferWidth = m_iWidth;
	m_dpps.BackBufferHeight = m_iHeight;
	m_dpps.BackBufferFormat = D3DFMT_A8R8G8B8;
	m_dpps.BackBufferCount = 1;
	m_dpps.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_dpps.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_dpps.hDeviceWindow = m_hWnd;
	m_dpps.Windowed = m_bWindowed;
	m_dpps.EnableAutoDepthStencil = TRUE;
	m_dpps.AutoDepthStencilFormat = D3DFMT_D24S8;
	m_dpps.Flags = 0;
	m_dpps.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_dpps.FullScreen_PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	RestoreDeviceObjects();

	return S_OK;
}

HRESULT RacorX3::RestoreDeviceObjects()
{
	HRESULT hr;

	IDirect3DDevice8* device;
	hr = m_spD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, m_iVP, &m_dpps, &device);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"CreateDevice failed!", L"Error", 0);
		return E_FAIL;
	}
	m_spDevice.reset(device, [](IDirect3DDevice8* device) { device->Release(); });

	IDirect3DVertexBuffer8* vb;
	hr = m_spDevice->CreateVertexBuffer(
		4 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&vb);
	if (FAILED(hr)) {
		MessageBox(m_hWnd, L"CreateVertexBuffer failed!", L"Error", 0);
		return E_FAIL;
	}
	m_spVB.reset(vb, [](IDirect3DVertexBuffer8* vb) { vb->Release(); });

	IDirect3DIndexBuffer8* ib;
	hr = m_spDevice->CreateIndexBuffer(
		6 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&ib);
	if (FAILED(hr)) {
		MessageBox(m_hWnd, L"CreateIndexBuffer", L"Error", 0);
		return E_FAIL;
	}
	m_spIB.reset(ib, [](IDirect3DIndexBuffer8* ib) { ib->Release(); });

	Vertex* vertices;
	m_spVB->Lock(0, 0, reinterpret_cast<BYTE**>(&vertices), 0);
	vertices[0] = { -100.0f, -100.0f, 0.0f, 0.0f, 0.0f, -1.0f };
	vertices[1] = { 100.0f, -100.0f, 0.0f, 0.0f, 0.0f, -1.0f };
	vertices[2] = { 100.0f, 100.0f, 0.0f, 0.0f, 0.0f, -1.0f };
	vertices[3] = { -100.0f, 100.0f, 0.0f, 0.0f, 0.0f, -1.0f };
	m_spVB->Unlock();

	WORD* indices;
	m_spIB->Lock(0, 0, reinterpret_cast<BYTE**>(&indices), 0);
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;
	m_spIB->Unlock();

	DWORD dwDecl[] = {
		D3DVSD_STREAM(0),
		D3DVSD_REG(0,D3DVSDT_FLOAT3),
		D3DVSD_REG(3,D3DVSDT_FLOAT3),
		D3DVSD_END()
	};

	hr = CreateVSFromBinFile(m_spDevice.get(), dwDecl, L"basic_light.vso", &m_dwVSH);

	m_spDevice->SetViewport(&m_Viewport);
	m_spDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	m_spDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_spDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	float material[] = { 0.0f, 0.2f, 0.3f, 0.0f };
	m_spDevice->SetVertexShaderConstant(DIFFUSE_COLOR, material, 1);
	float directionalLight[] = { 0.0f, 0.0f, 1.0f };
	m_spDevice->SetVertexShaderConstant(LIGHT_POSITION,directionalLight,1);
	float lightColor[] = { 0.1f, 0.3f, 0.1f };
	m_spDevice->SetVertexShaderConstant(LIGHT_COLOR, lightColor, 1);

	return S_OK;
}

HRESULT RacorX3::DeleteDeviceObjects()
{
	
	return S_OK;
}

HRESULT RacorX3::Render()
{
	

	m_spDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
	if (SUCCEEDED(m_spDevice->BeginScene())) {
		m_spDevice->SetVertexShader(m_dwVSH);
		m_spDevice->SetStreamSource(0, m_spVB.get(), sizeof(Vertex));
		m_spDevice->SetIndices(m_spIB.get(), 0);
		m_spDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 4, 0, 2);
		m_spDevice->EndScene();
	}
	m_spDevice->Present(0, 0, 0, 0);
	
	return S_OK;
}

HRESULT RacorX3::FrameMove(FLOAT)
{
	D3DXMATRIX Ry;
	D3DXMatrixRotationY(&Ry, 3.14f / 40.0f);
	D3DXMatrixMultiply(&m_mtWorld, &m_mtWorld, &Ry);
	D3DXMATRIX matTem;
	matTem = m_mtWorld * m_mtView * m_mtProj;
	m_spDevice->SetVertexShaderConstant(CLIP_MATRIX, &(matTem), 4);
	D3DXMATRIX mtWorldInverse;
	D3DXMatrixInverse(&mtWorldInverse, NULL, &m_mtWorld);
	m_spDevice->SetVertexShaderConstant(INVERSE_WORLD_MATRIX, &mtWorldInverse, 3);

	return S_OK;
}

HRESULT RacorX3::FinalCleanup()
{
	return S_OK;
}

const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL;
