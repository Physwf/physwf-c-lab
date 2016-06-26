#include "Demo.h"
#include <vector>

IDirect3DDevice9* Device;

ID3DXMesh* pMesh;
std::vector<D3DMATERIAL9> Mtrls(0);
std::vector<IDirect3DTexture9*> Textures(0);

ID3DXEffect* pLightTexEffect;

D3DXHANDLE hWorldMatrix;
D3DXHANDLE hViewMatrix;
D3DXHANDLE hProjMatrix;

D3DXHANDLE hTex;

D3DXHANDLE hLightTexTech;

bool Setup()
{
	HRESULT hr;

	ID3DXBuffer* mtrlBuffer = 0;
	DWORD numMtrl = 0;
	hr = D3DXLoadMeshFromX(
		L"mountain.x",
		D3DXMESH_MANAGED,
		Device,
		0,
		&mtrlBuffer,
		0,
		&numMtrl,
		&pMesh);

	if (FAILED(hr))
	{
		::MessageBoxA(0, "D3DXLoadMeshFromX() - Failed!", 0, 0);
		return false;
	}

	if (mtrlBuffer != 0 && numMtrl != 0)
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();
		for (DWORD i = 0; i < numMtrl; ++i)
		{
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;
			Mtrls.push_back(mtrls[i].MatD3D);

			if (mtrls[i].pTextureFilename != 0)
			{
				IDirect3DTexture9* tex = 0;
				D3DXCreateTextureFromFileA(
					Device,
					mtrls[i].pTextureFilename,
					&tex);
				Textures.push_back(tex);
			}
			else
			{
				Textures.push_back(0);
			}
		}
	}

	mtrlBuffer->Release();
	ID3DXBuffer* pError;
	hr = D3DXCreateEffectFromFile(
		Device,
		L"light_tex.txt",
		0,
		0,
		D3DXSHADER_DEBUG,
		0,
		&pLightTexEffect,
		&pError);
	if (FAILED(hr))
	{
		::MessageBoxA(0, (char*)pError->GetBufferPointer(), 0, 0);
		return false;
	}

	hWorldMatrix = pLightTexEffect->GetParameterByName(0, "WorldMatrix");
	hViewMatrix = pLightTexEffect->GetParameterByName(0, "ViewMatrix");
	hProjMatrix = pLightTexEffect->GetParameterByName(0, "ProjMatrix");
	hTex = pLightTexEffect->GetParameterByName(0, "Tex");

	hLightTexTech = pLightTexEffect->GetTechniqueByName("LightAndTexture");

	D3DXMATRIX W, P;

	D3DXMatrixIdentity(&W);
	pLightTexEffect->SetMatrix(hWorldMatrix, &W);

	D3DXMatrixPerspectiveFovLH(
		&P,
		D3DX_PI*0.25f,
		(float)Width / Height,
		1.0f, 1000.0f);
	pLightTexEffect->SetMatrix(hProjMatrix, &P);

	IDirect3DTexture9* tex = 0;
	D3DXCreateTextureFromFile(Device, L"Terrain_3x_diffcol.jpg", &tex);

	pLightTexEffect->SetTexture(hTex, tex);
	tex->Release();

	return true;
}

bool Display(float timeDelta)
{
	if (Device)
	{
		static float angle = (3.0f * D3DX_PI) / 2.0f;
		static float height = 5.0f;

		if (::GetAsyncKeyState(VK_LEFT) & 0x8000f)
			angle -= 0.5f * timeDelta;

		if (::GetAsyncKeyState(VK_RIGHT) & 0x8000f)
			angle += 0.5f * timeDelta;

		if (::GetAsyncKeyState(VK_UP) & 0x8000f)
			height += 5.0f * timeDelta;

		if (::GetAsyncKeyState(VK_DOWN) & 0x8000f)
			height -= 5.0f * timeDelta;

		D3DXVECTOR3 position(cosf(angle) * 10.0f, height, sinf(angle) * 10.0f);
		D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
		D3DXMATRIX V;
		D3DXMatrixLookAtLH(&V, &position, &target, &up);

		pLightTexEffect->SetMatrix(hViewMatrix, &V);

		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);

		Device->BeginScene();

		pLightTexEffect->SetTechnique(hLightTexTech);

		UINT numPasses = 0;
		pLightTexEffect->Begin(&numPasses, 0);

		for (UINT i = 0; i < numPasses; ++i)
		{
			pLightTexEffect->BeginPass(i);
			for (UINT j = 0; j < Mtrls.size();++j)
			{
				pMesh->DrawSubset(j);
			}
			pLightTexEffect->EndPass();
		}
		pLightTexEffect->End();
		Device->EndScene();
		Device->Present(0, 0, 0, 0);
	}
	return true;
}

void Cleanup()
{

}