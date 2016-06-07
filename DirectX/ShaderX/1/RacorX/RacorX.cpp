#include "RacorX.h"

const DWORD Vertex::FVF = D3DFVF_XYZ;

CRacorX::CRacorX() : CD3DApplication()
{
	m_fMaterial[0] = 1.0f;
	m_fMaterial[1] = 0.0f;
	m_fMaterial[2] = 0.0f;
	m_fMaterial[3] = 0.0f;
	
}

CRacorX::~CRacorX()
{

}

HRESULT CRacorX::Frame()
{
	FrameMove(0.0f);
	Render();
	return S_OK;
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
	m_spD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3DCaps);

	m_Viewport = { 0, 0, m_iWidth, m_iHeight };

	D3DXVECTOR3 eye = { 0.0f, 0.0f, -200.0f };
	D3DXVECTOR3 target = { 0.0f, 0.0f, 0.0f };
	D3DXVECTOR3 up = { 0.0f, 1.0f, 0.0f };
	D3DXMatrixLookAtLH(&m_mtView, &eye, &target, &up);
	float aspect = static_cast<float>(m_iWidth) / m_iHeight;
	D3DXMatrixPerspectiveFovLH(&m_mtProj, D3DX_PI*0.5, aspect, 1.0f, 1000.0f);

	D3DXMatrixIdentity(&m_mtWorld);

	return S_OK;
}

HRESULT CRacorX::InitDeviceObjects()
{
	if (m_D3DCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
		m_iVP = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	} else {
		m_iVP = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
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

	HRESULT rc = ConfirmDevice(&m_D3DCaps, m_iVP, D3DFMT_UNKNOWN);
	if (FAILED(rc)) {
		MessageBox(m_hWnd, L"ConfirmDevice failed", L"Error", 0);
		return S_FALSE;
	}
	RestoreDeviceObjects();
	return S_OK;
}

HRESULT CRacorX::RestoreDeviceObjects()
{
	IDirect3DDevice8* device;
	HRESULT hr = m_spD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_hWnd,
		m_iVP,
		&m_dpps,
		&device);
	if (FAILED(hr)) {
		OutputDebugString(L"Create Device Failed! Error:\n");
		switch (hr)
		{
		case D3DERR_DEVICELOST:
			OutputDebugString(L"D3DERR_DEVICELOST\n");
			break;
		case D3DERR_INVALIDCALL:
			OutputDebugString(L"D3DERR_INVALIDCALL\n");
			break;
		case D3DERR_NOTAVAILABLE:
			OutputDebugString(L"D3DERR_NOTAVAILABLE\n");
			break;
		case D3DERR_OUTOFVIDEOMEMORY:
			OutputDebugString(L"D3DERR_OUTOFVIDEOMEMORY\n");
			break;;
		default:
			OutputDebugString(L"Unknown\n");
			break;
		}
		return S_FALSE;
	}
	m_spDevice.reset(device, [](IDirect3DDevice8* device){ device->Release(); });
	DWORD dwDecl0[] = {
		D3DVSD_STREAM(0),
		D3DVSD_REG(0,D3DVSDT_FLOAT3),
		//D3DVSD_REG(5,D3DVSDT_D3DCOLOR),
		/*D3DVSD_CONST(0, 4),
		*(DWORD*)&m_mtWorld[0], *(DWORD*)&m_mtWorld[1], *(DWORD*)&m_mtWorld[2], *(DWORD*)&m_mtWorld[3],
		*(DWORD*)&m_mtWorld[4], *(DWORD*)&m_mtWorld[5], *(DWORD*)&m_mtWorld[6], *(DWORD*)&m_mtWorld[7],
		*(DWORD*)&m_mtWorld[8], *(DWORD*)&m_mtWorld[9], *(DWORD*)&m_mtWorld[10], *(DWORD*)&m_mtWorld[11],
		*(DWORD*)&m_mtWorld[12], *(DWORD*)&m_mtWorld[13], *(DWORD*)&m_mtWorld[14], *(DWORD*)&m_mtWorld[15],
		D3DVSD_CONST(0, 1),
		*(DWORD*)&m_fMaterial[0], *(DWORD*)&m_fMaterial[1], *(DWORD*)&m_fMaterial[2], *(DWORD*)&m_fMaterial[3],*/
		D3DVSD_END()
	};

	IDirect3DVertexBuffer8* vb;
	m_spDevice->CreateVertexBuffer(
		4 * sizeof (Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&vb);
	m_spVB.reset(vb, [](IDirect3DVertexBuffer8* vb){ vb->Release(); });

	Vertex* vertices = 0;
	m_spVB->Lock(0, 0, reinterpret_cast<BYTE**>(&vertices), 0);
	vertices[0] = { -100.0f, -100.0f, 0.0f, };
	vertices[1] = { 100.0f, -100.0f, 0.0f, };
	vertices[2] = { 100.0f, 100.0f, 0.0f, };
	vertices[3] = { -100.0f, 100.0f, 0.0f, };
	/*
	vertices[0] = { -1.0f, -1.0f, 0.2f, };
	vertices[1] = { 1.0f, -1.0f, 0.2f, };
	vertices[2] = { 1.0f, 1.0f, 0.2f, };
	vertices[3] = { -1.0f, 1.0f, 0.2f, };
	*/
	m_spVB->Unlock();

	IDirect3DIndexBuffer8* ib;
	m_spDevice->CreateIndexBuffer(
		6 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&ib);
	m_spIB.reset(ib, [](IDirect3DIndexBuffer8* ib){ ib->Release(); });

	WORD *indices = 0;
	m_spIB->Lock(0, 0, reinterpret_cast<BYTE**>(&indices), 0);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;

	m_spIB->Unlock();
	
	const char vsh[] = 
		"vs.1.1 \n" \
		"dp4 oPos.x, v0, c0 \n"\
		"dp4 oPos.y, v0, c1 \n"\
		"dp4 oPos.z, v0, c2 \n"\
		"dp4 oPos.w, v0, c3 \n"\
		"mov oD0, c4\n";
	/*
	const char vsh[] = 
		"vs.1.1 \n" \
		"mov oPos, v0 \n" \
		"mov oD0, c4 \n";
		*/
	ID3DXBuffer* pVBuffer;
	ID3DXBuffer* pErrors;
	HRESULT rc = D3DXAssembleShader(reinterpret_cast<LPCVOID>(vsh), sizeof(vsh) - 1, 0, NULL, &pVBuffer, &pErrors);
	if (FAILED(rc))
	{
		OutputDebugString(L"Failed to assemble the vertex shader, error:\n");
		OutputDebugStringA(reinterpret_cast<CHAR*>(pErrors->GetBufferPointer()));
		OutputDebugString(L"\n");
	}

	rc = m_spDevice->CreateVertexShader(dwDecl0, (DWORD*)pVBuffer->GetBufferPointer(), &m_dwVertexShader, 0);
	if (FAILED(rc))
	{
		OutputDebugString(L"Failed to create vertex shader, error:\n");
		WCHAR szBuffer[512] = { 0 };
		D3DXGetErrorString(rc, szBuffer, sizeof(szBuffer));
		OutputDebugString(szBuffer);
		OutputDebugString(L"\n");
	}
	m_spDevice->SetViewport(&m_Viewport);
	//m_spDevice->SetTransform(D3DTS_VIEW, &m_mtView);
	//m_spDevice->SetTransform(D3DTS_PROJECTION, &m_mtProj);
	m_spDevice->SetRenderState(D3DRS_ZENABLE, true);
	m_spDevice->SetRenderState(D3DRS_LIGHTING, false);
	//m_spDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_spDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	return S_OK;
}

HRESULT CRacorX::DeleteDeviceObjects()
{
	return S_OK;
}

HRESULT CRacorX::Render()
{
	D3DXMATRIX mat;
	//mat = m_mtWorld * m_mtView * m_mtProj;
	D3DXMatrixMultiply(&mat, &m_mtView, &m_mtProj);
	D3DXMatrixTranspose(&mat, &mat);
	HRESULT hr;
	m_spDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);

	if (SUCCEEDED(m_spDevice->BeginScene())) 
	{
		m_spDevice->SetStreamSource(0, m_spVB.get(), (sizeof Vertex));
		m_spDevice->SetIndices(m_spIB.get(), 0);
		hr = m_spDevice->SetVertexShader(m_dwVertexShader);
		hr = m_spDevice->SetVertexShaderConstant(0, &mat, 4);
		hr = m_spDevice->SetVertexShaderConstant(4, &m_fMaterial, 1);
		m_spDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 4, 0, 2);
		m_spDevice->EndScene();
	}

	m_spDevice->Present(0, 0, 0, 0);

	return S_OK;
}

HRESULT CRacorX::FrameMove(FLOAT)
{
	D3DXMATRIX Ry;
	D3DXMatrixRotationY(&Ry, 3.14f / 40.0f);
	//m_mtWorld = m_mtWorld * Ry;
	//D3DXMatrixMultiply(&m_mtWorld, &m_mtWorld, &Ry);
	return S_OK;
}

HRESULT CRacorX::FinalCleanup()
{
	return S_OK;
}
