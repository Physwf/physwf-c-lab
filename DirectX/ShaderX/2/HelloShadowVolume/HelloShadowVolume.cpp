#include "HelloShadowVolume.h"

HelloShadowVolume::HelloShadowVolume()
{

}

HelloShadowVolume::~HelloShadowVolume()
{

}


HRESULT HelloShadowVolume::Frame()
{
	FrameMove(0.0f);
	Render();
	return S_OK;
}

HRESULT HelloShadowVolume::OneTimeSceneInit()
{
	IDirect3D8* d3d = Direct3DCreate8(D3D_SDK_VERSION);
	if (!d3d)
	{
		MessageBox(0, L"Direct3DCreate8 error", 0, 0);
		return E_FAIL;
	}
	m_spD3D.reset(d3d, [](IDirect3D8* d3d){ d3d->Release(); });

	return S_OK;
}

HRESULT HelloShadowVolume::InitDeviceObjects()
{
	m_dpps.AutoDepthStencilFormat = D3DFMT_D24S8;
	m_dpps.BackBufferCount = 1;
	m_dpps.BackBufferFormat = D3DFMT_A8R8G8B8;
	m_dpps.BackBufferWidth = m_iWidth;
	m_dpps.BackBufferHeight = m_iHeight;
	m_dpps.EnableAutoDepthStencil = TRUE;
	m_dpps.Flags = 0;
	m_dpps.FullScreen_PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	m_dpps.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_dpps.hDeviceWindow = m_hWnd;
	m_dpps.Windowed = true;
	m_dpps.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_dpps.SwapEffect = D3DSWAPEFFECT_DISCARD;

	return RestoreDeviceObjects();
}

HRESULT HelloShadowVolume::RestoreDeviceObjects()
{
	HRESULT hr;
	IDirect3DDevice8* device;
	hr = m_spD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&m_dpps,
		&device);
	if (FAILED(hr))
	{
		MessageBox(0, L"CreateDevice failed", 0, 0);
		return E_FAIL;
	}
	m_spDevice.reset(device, [](IDirect3DDevice8* device){ device->Release(); });

	m_spDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	m_spDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_spDevice->SetRenderState(D3DRS_DITHERENABLE, TRUE);
	D3DVIEWPORT8 viewport = { 0, 0, m_iWidth, m_iHeight };
	m_spDevice->SetViewport(&viewport);

	D3DXVECTOR3 eye(0.0f, 0.0f, 10.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_mtView, &eye, &target, &up);

	D3DXMatrixPerspectiveFovLH(&m_mtProj, 0.2*D3DX_PI, (float)m_iWidth / (float)m_iHeight, 1.0f, 100.f);

	m_cPlaneTint = { 0.7f, 0.6f, 0.4f, 1.0f };

	DWORD decl[] = {
		D3DVSD_STREAM(0),
		D3DVSD_REG(0, D3DVSDT_FLOAT3),
		//D3DVSD_REG(3, D3DVSDT_FLOAT3),
		D3DVSD_END()
	};
	hr = CreateVSFromBinFile(m_spDevice.get(), decl, L"plane.vso", &m_dwPlaneVSH);
	if (FAILED(hr))
	{
		MessageBox(0, 0, L"CreateVSFromBinFile failed", 0);
		return E_FAIL;
	}
	hr = CreatePSFromBinFile(m_spDevice.get(), L"plane.pso", &m_dwPlanePSH);
	if (FAILED(hr))
	{
		MessageBox(0, 0, L"CreatePSFromBinFile failed", 0);
		return E_FAIL;
	}
	ID3DXMesh* plane;
	//D3DXCreatePolygon(m_spDevice.get(), 2.0f, 4, &plane, NULL);
	CreatePlane(m_spDevice.get(), 10.0f, 10, &plane);
	//D3DXCreateSphere(m_spDevice.get(), 1.0f,20,20, &plane, NULL);
	m_spHerizonPlane.reset(plane, [](ID3DXMesh* plane){plane->Release(); });

	IDirect3DVertexBuffer8* vb;
	IDirect3DIndexBuffer8* ib;
	plane->GetVertexBuffer(&vb);
	plane->GetIndexBuffer(&ib);
	m_spPlaneVB.reset(vb, [](IDirect3DVertexBuffer8* vb){vb->Release(); });
	m_spPlaneIB.reset(ib, [](IDirect3DIndexBuffer8* ib){ib->Release(); });
	m_dwPlaneNumVertices = plane->GetNumFaces();
	m_dwPlaneNumFaces = plane->GetNumFaces();
	m_spDevice->SetPixelShaderConstant(0, m_cPlaneTint, 1);

	D3DXMATRIX w;
	D3DXMatrixIdentity(&w);
	D3DXMATRIX temp = w*m_mtView*m_mtProj;
	D3DXMatrixTranspose(&temp, &temp);
	m_spDevice->SetVertexShaderConstant(0, &temp, 4);
	//
	return S_OK;
}

HRESULT HelloShadowVolume::DeleteDeviceObjects()
{
	return S_OK;
}

HRESULT HelloShadowVolume::Render()
{
	m_spDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
	if (SUCCEEDED( m_spDevice->BeginScene()))
	{
		//m_spDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		m_spDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		m_spDevice->SetVertexShader(m_dwPlaneVSH);
		m_spDevice->SetPixelShader(m_dwPlanePSH);
		
		
		//m_spHerizonPlane->DrawSubset(0);
		m_spDevice->SetStreamSource(0, m_spPlaneVB.get(), sizeof Vertex);
		m_spDevice->SetIndices(m_spPlaneIB.get(),0);
		m_spDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, m_dwPlaneNumVertices, 0, m_dwPlaneNumFaces);
		m_spDevice->EndScene();
	}
	m_spDevice->Present(0, 0, 0, 0);
	return S_OK;

}

HRESULT HelloShadowVolume::FrameMove(FLOAT)
{
	return S_OK;

}

HRESULT HelloShadowVolume::FinalCleanup()
{
	return S_OK;

}
