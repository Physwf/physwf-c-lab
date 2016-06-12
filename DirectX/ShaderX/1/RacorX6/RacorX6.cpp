#include "RacorX6.h"
#include "const.h"
RacorX6::RacorX6()
{
	m_fObjectRadius = 1.0f;
	ZeroMemory(m_bKey, 256);
}

RacorX6::~RacorX6()
{

}

HRESULT RacorX6::Frame()
{
	FrameMove(1.1f);
	Render();
	return S_OK;
}

HRESULT RacorX6::ConfirmDevice(D3DCAPS8* pCaps, DWORD dwBehavior, D3DFORMAT Format)
{
	if ((dwBehavior & D3DCREATE_HARDWARE_VERTEXPROCESSING) || (D3DCREATE_MIXED_VERTEXPROCESSING))
	{
		if (pCaps->VertexShaderVersion < D3DVS_VERSION(1, 1))
			return E_FAIL;
		if (pCaps->PixelShaderVersion < D3DPS_VERSION(1, 1))
			return E_FAIL;
		if (pCaps->PixelShaderVersion < D3DPS_VERSION(1, 4))
			m_bPS14Avaliable = false;
	}
	return S_OK;
}

HRESULT RacorX6::OneTimeSceneInit()
{
	IDirect3D8* d3d = Direct3DCreate8(D3D_SDK_VERSION);
	if (d3d == nullptr)
	{
		MessageBox(m_hWnd, L"Direct3DCreate8 failed!", L"Error", 0);
		return E_FAIL;
	}
	m_spD3D.reset(d3d, [](IDirect3D8* d3d) { d3d->Release(); });
	m_spD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3DCaps);

	D3DXMatrixPerspectiveFovLH(&m_mtProj, D3DX_PI*0.5, static_cast<float>(m_iWidth) / m_iHeight, m_fObjectRadius / 64.0f,
		m_fObjectRadius*200.0f);
	D3DXMatrixTranslation(&m_mtWorld, -m_vObjectCenter.x, -m_vObjectCenter.x, -m_vObjectCenter.x);

	m_ArcBall.SetWindow(m_iWidth, m_iHeight, 0.85f);
	m_ArcBall.SetRadius(m_fObjectRadius);

	m_Viewport = { 0, 0, m_iWidth, m_iHeight };


	return S_OK;
}

HRESULT RacorX6::InitDeviceObjects()
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

HRESULT RacorX6::RestoreDeviceObjects()
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

	LPD3DXMESH pSphere;
	CreateSphereMesh(m_spDevice.get(), &pSphere);

	DWORD dwDecl[MAX_FVF_DECL_SIZE];
	pSphere->GetDeclaration(dwDecl);

	hr = CreateVSFromBinFile(m_spDevice.get(), dwDecl, L"diff.vso", &m_dwVSH);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"CreateVSFromBinFile failed!", L"Error", 0);
		return E_FAIL;
	}
	
	IDirect3DTexture8* color_map;
	hr = D3DXCreateTextureFromFile(m_spDevice.get(), _T("earth.bmp"), &color_map);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"D3DXCreateTextureFromFile failed!", L"Error", 0);
		return E_FAIL;
	}
	m_spColorMap.reset(color_map, [](IDirect3DTexture8* color_map){ color_map->Release(); });

	IDirect3DTexture8* heightMap;
	hr = D3DXCreateTextureFromFile(m_spDevice.get(), _T("earthbump.bmp"), &heightMap);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"D3DXCreateTextureFromFile failed!", L"Error", 0);
		return E_FAIL;
	}
	m_spHeightMap.reset(color_map, [](IDirect3DTexture8* colorMap) { colorMap->Release(); });

	D3DSURFACE_DESC desc;
	m_spHeightMap->GetLevelDesc(0, &desc);

	IDirect3DTexture8* normalMap;
	hr = D3DXCreateTexture(m_spDevice.get(), desc.Width, desc.Height, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &normalMap);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"D3DXCreateTexture failed!", L"Error", 0);
		return E_FAIL;
	}
	m_spNormalMap.reset(normalMap, [](IDirect3DTexture8* normalMap){ normalMap->Release(); });

	D3DXComputeNormalMap(m_spNormalMap.get(), m_spHeightMap.get(), NULL, 0, D3DX_CHANNEL_RED, 10);

	

	m_spDevice->SetViewport(&m_Viewport);

	m_spDevice->SetRenderState(D3DRS_DITHERENABLE, TRUE);
	m_spDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	m_spDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_spDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//m_spDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_spDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	m_spDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	m_spDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	m_spDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	m_spDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	m_spDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	m_spDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
	m_spDevice->SetTextureStageState(0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
	m_spDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
	m_spDevice->SetTextureStageState(0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
	m_spDevice->SetTextureStageState(0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);

	m_spDevice->SetVertexShaderConstant(SPEC_POWER, D3DXVECTOR4(0,10,25,50),1);

	//D3DXVECTOR3 vLight(0, 0, 1);
	//m_spDevice->SetVertexShaderConstant(LIGHT_POSITION, vLight, 1);

	D3DXCOLOR matDiffuse(0.9f, 0.9f, 0.9f, 1.0f);
	m_spDevice->SetVertexShaderConstant(DIFFUSE_COLOR, &matDiffuse, 1);

	D3DXVECTOR4 Attenuation = { 1.0f, 0.0f, 0.0f, 0.0f };
	m_spDevice->SetVertexShaderConstant(LIGHT_ATTENUATION, Attenuation, 1);

	return S_OK;
}

HRESULT RacorX6::DeleteDeviceObjects()
{
	
	return S_OK;
}

HRESULT RacorX6::Render()
{
	m_spDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
	if (SUCCEEDED(m_spDevice->BeginScene())) {
		m_spDevice->SetVertexShader(m_dwVSH);
		m_spDevice->SetTexture(0, m_spColorMap.get());

		m_spDevice->EndScene();
	}
	m_spDevice->Present(0, 0, 0, 0);
	
	return S_OK;
}

HRESULT RacorX6::FrameMove(FLOAT delta)
{
	//D3DXMATRIX Ry;
	//D3DXMatrixRotationY(&Ry, 3.14f / 40.0f);
	//D3DXMatrixMultiply(&m_mtWorld, &m_mtWorld, &Ry);
	//m_spDevice->SetTransform(D3DTS_WORLD, &m_mtWorld);
	D3DXMatrixTranslation(&m_mtWorld, -m_vObjectCenter.x, -m_vObjectCenter.x, -m_vObjectCenter.x);
	D3DXMatrixMultiply(&m_mtWorld, &m_mtWorld, m_ArcBall.GetTranslationMatrix());
	D3DXMatrixMultiply(&m_mtWorld, &m_mtWorld, m_ArcBall.GetRotationMatrix());

	m_spDevice->SetVertexShaderConstant(WORLD_MATRIX, &m_mtWorld, 4);

	D3DXVECTOR3 pos(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 eye(0.0f, 0.0f, -3.7f * m_fObjectRadius + m_fZDist);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_mtView, &eye, &pos, &up);

	m_spDevice->SetVertexShaderConstant(CLIP_MATRIX, &(m_mtWorld*m_mtView*m_mtProj), 4);

	D3DXMATRIX inverseWorld;
	D3DXMatrixInverse(&inverseWorld, NULL, &m_mtWorld);
	m_spDevice->SetVertexShaderConstant(INVERSE_WORLD_MATRIX, inverseWorld, 3);

	m_spDevice->SetVertexShaderConstant(EYE_VECTOR, eye, 1);

	return S_OK;
}

HRESULT RacorX6::FinalCleanup()
{
	return S_OK;
}

HRESULT CALLBACK RacorX6::MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	m_ArcBall.HandleMouseMessages(hwnd, msg, wParam, lParam);
	switch (msg)
	{
	case WM_KEYDOWN:
		m_bKey[wParam] = 1;
		break;
	case WM_KEYUP:
		m_bKey[wParam] = 0;
		break;
	case WM_MOUSEWHEEL:
	{
		short sr = HIWORD(wParam);
		m_fZDist -= (sr / 120) * m_fObjectRadius;
	}
		break;
	}
	return CD3DApplication::MessageHandler(hwnd, msg, wParam, lParam);
}

