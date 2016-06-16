#include "RacorX8.h"
#include <sstream>
#include "const.h"
#include <math.h>

RacorX8::RacorX8()
{
	m_fObjectRadius = 1.0f;
	ZeroMemory(m_bKey, 256);
}

RacorX8::~RacorX8()
{

}

HRESULT RacorX8::Frame()
{
	FrameMove(1.1f);
	Render();
	return S_OK;
}

HRESULT RacorX8::ConfirmDevice(D3DCAPS8* pCaps, DWORD dwBehavior, D3DFORMAT Format)
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

HRESULT RacorX8::OneTimeSceneInit()
{
	IDirect3D8* d3d = Direct3DCreate8(D3D_SDK_VERSION);
	if (d3d == nullptr)
	{
		MessageBox(m_hWnd, L"Direct3DCreate8 failed!", L"Error", 0);
		return E_FAIL;
	}
	m_spD3D.reset(d3d, [](IDirect3D8* d3d) { d3d->Release(); });
	m_spD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_D3DCaps);

	D3DXMatrixPerspectiveFovLH(&m_mtProj,0.55f, static_cast<float>(m_iWidth) / m_iHeight, 1.0f, 10000.0f);

	//D3DXMatrixTranslation(&m_mtWorld, -m_vObjectCenter.x, -m_vObjectCenter.x, -m_vObjectCenter.x);
	D3DXMatrixIdentity(&m_mtWorld);
	D3DXMatrixRotationX(&m_mtWorld, D3DX_PI / 2);
	m_ArcBall.SetWindow(m_iWidth, m_iHeight, 0.85f);
	m_ArcBall.SetRadius(m_fObjectRadius);

	m_Viewport = { 0, 0, m_iWidth, m_iHeight };


	return S_OK;
}

HRESULT RacorX8::InitDeviceObjects()
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

HRESULT RacorX8::RestoreDeviceObjects()
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

	//CreateSphere();

	LoadXFile("sphere.x");

	IDirect3DVertexBuffer8* vbNormal;
	hr = m_spDevice->CreateVertexBuffer(m_iNumVertices * 2 * sizeof SimpleVertex, D3DUSAGE_WRITEONLY, D3DFVF_XYZ, D3DPOOL_MANAGED, &vbNormal);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"CreateVertexBuffer failed!", L"Error", 0);
		return E_FAIL;
	}
	hr = CreateNormal<ShaderVertex, SimpleVertex>(m_spVB.get(), vbNormal);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"CreateNormal failed!", L"Error", 0);
		return E_FAIL;
	}
	m_spVBNormal.reset(vbNormal, [](IDirect3DVertexBuffer8* vbNormal){vbNormal->Release(); });

	IDirect3DVertexBuffer8* vbTangent;
	hr = m_spDevice->CreateVertexBuffer(m_iNumVertices * 2 * sizeof SimpleVertex, D3DUSAGE_WRITEONLY, D3DFVF_XYZ, D3DPOOL_MANAGED, &vbTangent);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"CreateVertexBuffer failed!", L"Error", 0);
		return E_FAIL;
	}
	hr = CreateTangent<ShaderVertex, SimpleVertex>(m_spVB.get(), vbTangent);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"CreateTangent failed!", L"Error", 0);
		return E_FAIL;
	}
	m_spVBTangent.reset(vbTangent, [](IDirect3DVertexBuffer8* vbTangent){vbTangent->Release(); });

	//DWORD dwDecl[MAX_FVF_DECL_SIZE];
	//ZeroMemory(dwDecl, sizeof dwDecl);
	//pSphere->GetDeclaration(dwDecl);
	DWORD decl[] = {
		D3DVSD_STREAM(0),
		D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_FLOAT3),
		D3DVSD_REG(D3DVSDE_NORMAL, D3DVSDT_FLOAT3),
		D3DVSD_REG(D3DVSDE_TEXCOORD0, D3DVSDT_FLOAT2),
		D3DVSD_REG(D3DVSDE_TEXCOORD1, D3DVSDT_FLOAT3),
		D3DVSD_END()
	};
	hr = CreateVSFromBinFile(m_spDevice.get(), decl, L"specular.vso", &m_dwVSH);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"CreateVSFromBinFile failed!", L"Error", 0);
		return E_FAIL;
	}

	hr = CreatePSFromBinFile(m_spDevice.get(), L"specular.pso", &m_dwPSH);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"CreatePSFromBinFile failed!", L"Error", 0);
		return E_FAIL;
	}

	hr = CreatePSFromBinFile(m_spDevice.get(), L"specularBump.pso", &m_dwPSHBump);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"CreatePSFromBinFile failed!", L"Error", 0);
		return E_FAIL;
	}

	if (m_bPS14Avaliable)
	{
		hr = CreatePSFromBinFile(m_spDevice.get(), L"specularBump14.pso", &m_dwPSHBump14);
		if (FAILED(hr))
		{
			MessageBox(m_hWnd, L"CreatePSFromBinFile failed!", L"Error", 0);
			return E_FAIL;
		}
	}
	DWORD declLine[] = {
		D3DVSD_STREAM(0),
		D3DVSD_REG(D3DVSDE_POSITION, D3DVSDT_FLOAT3),
		D3DVSD_END()
	};
	hr = CreateVSFromBinFile(m_spDevice.get(), declLine, L"line.vso", &m_dwVSHLine);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"CreateVSFromBinFile failed!", L"Error", 0);
		return E_FAIL;
	}
	hr = CreatePSFromBinFile(m_spDevice.get(), L"line.pso", &m_dwVPHLine);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"CreatePSFromBinFile failed!", L"Error", 0);
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
	m_spHeightMap.reset(heightMap, [](IDirect3DTexture8* heightMap) { heightMap->Release(); });

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

	hr = D3DXComputeNormalMap(m_spNormalMap.get(), m_spHeightMap.get(), NULL, 0, D3DX_CHANNEL_RED, 10);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"D3DXComputeNormalMap failed!", L"Error", 0);
		return E_FAIL;
	}
	
	IDirect3DTexture8* power;
	hr = D3DXCreateTexture(m_spDevice.get(), 256, 256, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &power);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"D3DXCreateTexture failed!", L"Error", 0);
		return E_FAIL;
	}
	m_spPower.reset(power, [](IDirect3DTexture8* power){ power->Release();  });
	FLOAT fPower = 16.0f;
	hr = D3DXFillTexture(power, LightEval, &fPower);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"D3DXFillTexture failed!", L"Error", 0);
		return E_FAIL;
	}

	m_spDevice->SetViewport(&m_Viewport);

	m_spDevice->SetRenderState(D3DRS_DITHERENABLE, TRUE);
	m_spDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	
	m_spDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	m_spDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_spDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

	//m_spDevice->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	//m_spDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//m_spDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	//m_spDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	//m_spDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//m_spDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	//m_spDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	//m_spDevice->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_DISABLE);
	m_spDevice->SetTextureStageState(0, D3DTSS_MINFILTER, D3DTEXF_LINEAR);
	m_spDevice->SetTextureStageState(0, D3DTSS_MAGFILTER, D3DTEXF_LINEAR);
	//m_spDevice->SetTextureStageState(0, D3DTSS_MIPFILTER, D3DTEXF_LINEAR);
	//m_spDevice->SetTextureStageState(0, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
	//m_spDevice->SetTextureStageState(0, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);

	m_spDevice->SetTextureStageState(2, D3DTSS_ADDRESSU, D3DTADDRESS_CLAMP);
	m_spDevice->SetTextureStageState(2, D3DTSS_ADDRESSV, D3DTADDRESS_CLAMP);

	D3DXVECTOR4 vLight(0.0f, 0.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&vLight, &vLight);
	m_spDevice->SetVertexShaderConstant(12, &vLight, 1);

	D3DXVECTOR4 half(0.5f, 0.5f, 0.5f, 0.5f);
	m_spDevice->SetVertexShaderConstant(33, &half, 1);

	return S_OK;
}

HRESULT RacorX8::DeleteDeviceObjects()
{
	
	return S_OK;
}

HRESULT RacorX8::Render()
{
	HRESULT hr;
	m_spDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
	if (SUCCEEDED(m_spDevice->BeginScene())) {
		hr = m_spDevice->SetTexture(3, m_spColorMap.get());
		hr = m_spDevice->SetVertexShader(m_dwVSH);
		if (m_bBump)
		{
			hr = m_spDevice->SetTexture(0, m_spNormalMap.get());
			hr = m_spDevice->SetTexture(1, m_spPower.get());
			hr = m_spDevice->SetTexture(2, m_spPower.get());
			if (m_bPixelShader)
			{
				hr = m_spDevice->SetPixelShader(m_dwPSHBump14);
			}
			else
			{
				hr = m_spDevice->SetPixelShader(m_dwPSHBump);
			}
		}
		else
		{
			hr = m_spDevice->SetPixelShader(m_dwPSH);
		}
		//hr = m_spEarthMesh->DrawSubset(0);
		m_spDevice->SetStreamSource(0, m_spVB.get(), sizeof ShaderVertex);
		m_spDevice->SetIndices(m_spIB.get(), 0);
		m_spDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, m_iNumVertices, 0, m_iNumTriangles);
		//draw lines
		if (m_bShowTangent || m_bShowNormal)
		{
			m_spDevice->SetTexture(0, 0);
			m_spDevice->SetTexture(2, 0);
			m_spDevice->SetTexture(3, 0);
			m_spDevice->SetVertexShader(m_dwVSHLine);
			m_spDevice->SetPixelShader(m_dwVPHLine);
			if (m_bShowTangent)
			{
				m_spDevice->SetStreamSource(0, m_spVBTangent.get(), sizeof SimpleVertex);
				m_spDevice->DrawPrimitive(D3DPT_LINELIST, 0, m_iNumVertices);
			}
			if (m_bShowNormal)
			{
				m_spDevice->SetStreamSource(0, m_spVBNormal.get(), sizeof SimpleVertex);
				m_spDevice->DrawPrimitive(D3DPT_LINELIST, 0, m_iNumVertices);
			}
		}
		
		
		hr = m_spDevice->EndScene();
	}
	m_spDevice->Present(0, 0, 0, 0);
	
	return S_OK;
}

HRESULT RacorX8::FrameMove(FLOAT delta)
{
	D3DXMATRIX Ry;
	D3DXMatrixRotationY(&Ry, 0.01f);
	D3DXMatrixMultiply(&m_mtWorld, &m_mtWorld, &Ry);
	//D3DXMatrixTranslation(&m_mtWorld, -m_vObjectCenter.x, -m_vObjectCenter.x, -m_vObjectCenter.x);
	//D3DXMatrixMultiply(&m_mtWorld, &m_mtWorld, m_ArcBall.GetTranslationMatrix());
	//D3DXMatrixMultiply(&m_mtWorld, &m_mtWorld, m_ArcBall.GetRotationMatrix());

	//m_spDevice->SetVertexShaderConstant(TRASPOSED_WORLD_MATRIX, &m_mtWorld, 4);
	//D3DXMatrixIdentity(&m_mtWorld);
	
	D3DXVECTOR3 pos(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 eye(0.0f, 0.0f, -5.f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_mtView, &eye, &pos, &up);

	D3DXMATRIX matTemp;
	D3DXMatrixTranspose(&matTemp, &m_mtWorld);
	m_spDevice->SetVertexShaderConstant(0, &matTemp, 4);

	matTemp = m_mtWorld*m_mtView*m_mtProj;
	D3DXMatrixTranspose(&matTemp, &(m_mtWorld*m_mtView*m_mtProj));
	m_spDevice->SetVertexShaderConstant(8, &matTemp, 4);
	
	m_spDevice->SetVertexShaderConstant(24, &eye, 1);

	//m_spDevice->SetVertexShaderConstant(EYE_VECTOR, eye, 1);
	if (m_bKey['B']) { m_bKey['B'] = 0; m_bBump = !m_bBump; };
	if (m_bKey['P'] && m_bPS14Avaliable) { m_bKey['P'] = 0; m_bPixelShader = !m_bPixelShader; };
	if (m_bKey['N']) { m_bKey['N'] = 0; m_bShowNormal = !m_bShowNormal; };
	if (m_bKey['T']) { m_bKey['T'] = 0; m_bShowTangent = !m_bShowTangent; };
	return S_OK;
}

HRESULT RacorX8::FinalCleanup()
{
	return S_OK;
}

HRESULT CALLBACK RacorX8::MessageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

HRESULT RacorX8::CreateSphere()
{
	HRESULT hr;
	LPD3DXMESH pSphere;
	hr = CreateSphereMesh(m_spDevice.get(), &pSphere);
	m_spEarthMesh.reset(pSphere, [](LPD3DXMESH sphere){ sphere->Release(); });
	IDirect3DIndexBuffer8* ib;
	m_spEarthMesh->GetIndexBuffer(&ib);
	m_spIB.reset(ib, [](IDirect3DIndexBuffer8* ib){ib->Release(); });
	IDirect3DVertexBuffer8* vb;
	m_spEarthMesh->GetVertexBuffer(&vb);
	m_spVB.reset(vb, [](IDirect3DVertexBuffer8* vb){vb->Release(); });
	m_iNumTriangles = m_spEarthMesh->GetNumFaces();
	m_iNumVertices = m_spEarthMesh->GetNumVertices();
	return hr;
}

HRESULT RacorX8::LoadXFile(const LPSTR name)
{
	HRESULT hr;
	LPD3DXMESH pMesh, pClone;

	if (FAILED(D3DXLoadMeshFromX(name, D3DXMESH_SYSTEMMEM, m_spDevice.get(), NULL, NULL, NULL, &pMesh)))
	{
		MessageBox(m_hWnd, L"D3DXLoadMeshFromX failed!", L"Error", 0);
		return E_FAIL;
	}

	hr = pMesh->CloneMeshFVF(D3DXMESH_MANAGED, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX2 | D3DFVF_TEXCOORDSIZE3(1), m_spDevice.get(), &pClone);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"CloneMeshFVF failed!", L"Error", 0);
		return E_FAIL;
	}

	hr = D3DXComputeTangent(pMesh, 0, pClone, 1, D3DX_COMP_TANGENT_NONE, TRUE, NULL);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"D3DXComputeTangent failed!", L"Error", 0);
		return E_FAIL;
	}

	IDirect3DIndexBuffer8* ib;
	hr = pClone->GetIndexBuffer(&ib);
	m_spIB.reset(ib, [](IDirect3DIndexBuffer8* ib){ib->Release(); });
	IDirect3DVertexBuffer8* vb;
	hr = pClone->GetVertexBuffer(&vb);
	m_spVB.reset(vb, [](IDirect3DVertexBuffer8* vb){vb->Release(); });

	m_iNumTriangles = pClone->GetNumFaces();
	m_iNumVertices = pClone->GetNumVertices();

	pMesh->Release();
	pClone->Release();
	return S_OK;
}

void LightEval(D3DXVECTOR4 *col, D3DXVECTOR2 *input, D3DXVECTOR2 *sampleSize, void *pfPower)
{
	float fPower = (float)pow(input->y, *(float*)pfPower);
	col->x = fPower;
	col->y = fPower;
	col->z = fPower;
	col->w = input->x;
}
