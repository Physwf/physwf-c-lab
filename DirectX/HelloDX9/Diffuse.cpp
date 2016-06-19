#include "Demo.h"

IDirect3DDevice9* Device;

IDirect3DVertexDeclaration9* pVD;
IDirect3DVertexShader9* pVSH;
ID3DXConstantTable *pConsts;
ID3DXMesh* pTeapot;
D3DXMATRIX mt_Proj;
D3DXMATRIX mt_View;
D3DXMATRIX mt_World;

D3DXHANDLE hMVP;
D3DXHANDLE hWorld;
D3DXHANDLE hMaterial;
D3DXHANDLE hDirLight;

bool Setup()
{
	HRESULT hr;

	D3DVIEWPORT9 viewport = { 0, 0, Width, Height };
	Device->SetViewport(&viewport);

	Device->SetRenderState(D3DRS_ZENABLE, true);
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	D3DXCreateTeapot(Device, &pTeapot, NULL);
	D3DVERTEXELEMENT9 elems[] = 
	{
		{0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},
		{0,12,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_NORMAL,0},
		D3DDECL_END()
	};
	hr = Device->CreateVertexDeclaration(elems, &pVD);
	if (FAILED(hr))
	{
		::MessageBox(0, L"CreateVertexDeclaration failed", L"Error", 0);
		return false;
	}
	Device->SetVertexDeclaration(pVD);

	ID3DXBuffer* pBuffer, *pError;

	
	hr = D3DXCompileShaderFromFile(L"Diffuse.txt", 0, 0, "Main", "vs_2_0", D3DXSHADER_DEBUG, &pBuffer, &pError, &pConsts);
	if (FAILED(hr))
	{
		::MessageBox(0, L"D3DXCompileShaderFromFile failed", L"Error", 0);
		OutputDebugStringA((CHAR*)pError->GetBufferPointer());
		return false;
	}

	hMVP = pConsts->GetConstantByName(0, "WorldViewProj");
	hWorld = pConsts->GetConstantByName(0, "World");
	hMaterial = pConsts->GetConstantByName(0, "Material");
	hDirLight = pConsts->GetConstantByName(0, "DirLight");

	hr = Device->CreateVertexShader((DWORD*)pBuffer->GetBufferPointer(), &pVSH);
	if (FAILED(hr))
	{
		::MessageBox(0, L"CreateVertexShader failed", L"Error", 0);
		return false;
	}
	D3DXMatrixPerspectiveFovLH(&mt_Proj, D3DX_PI*0.2f, (float)Width / (float)Height, 1.0f, 1000.0f);
	D3DXVECTOR3 eye(0.0f, 0.0f, -7.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 at(0.0f, 0.0f, 0.0f);
	D3DXMatrixLookAtLH(&mt_View, &eye, &at, &up);

	D3DXMatrixIdentity(&mt_World);
	/*
	float DirLight[4] = { 0.0f, 0.0f, 1.0f, 0.0f };
	float Material[4] = { 0.3f, 0.5f, 0.7f, 1.0f };
	pConsts->SetFloatArray(Device, hDirLight, DirLight, 4);
	pConsts->SetFloatArray(Device, hMaterial, Material, 4);
	*/

	D3DXVECTOR4 DirLight = { 1.0f, 0.0f, 0.0f, 0.0f };
	D3DXVECTOR4 Material = { 0.8f, 0.0f, 0.0f, 0.0f };
	pConsts->SetVector(Device, hDirLight, &DirLight);
	pConsts->SetVector(Device, hMaterial, &Material);
	

	return true;
}

void Cleanup()
{

}

bool Display(float timeDelta)
{
	Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
	if (SUCCEEDED(Device->BeginScene()))
	{
		Device->SetVertexShader(pVSH);
		D3DXMATRIX Ry;
		D3DXMatrixRotationY(&Ry, 0.0001f);
		D3DXMatrixMultiply(&mt_World, &mt_World, &Ry);
		pConsts->SetMatrix(Device, hMVP, &(mt_World*mt_View*mt_Proj));
		pConsts->SetMatrix(Device, hWorld, &mt_World);
		pTeapot->DrawSubset(0);
		Device->EndScene();
	}
	Device->Present(0, 0, 0, 0);
	return true;
}