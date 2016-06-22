#include "Demo.h"
#include <set>
#include <sstream>

IDirect3DDevice9* Device;
ID3DXMesh* pMesh;
IDirect3DVertexBuffer9* pEdges;
IDirect3DIndexBuffer9* pEdgeIndices;
IDirect3DTexture9* pBrightTexture;
IDirect3DVertexShader9* pToonSH;
ID3DXConstantTable* pToonConst;
IDirect3DVertexShader9* pEdgeSH;
ID3DXConstantTable* pEdgeConst;
IDirect3DVertexDeclaration9* pToonDecl;
IDirect3DVertexDeclaration9* pEdgeDecl;
DWORD numEdgeVertices;
DWORD numEdges;

D3DXHANDLE hToonWVP;
D3DXHANDLE hToonWorld;
D3DXHANDLE hDirLight;
D3DXHANDLE hToonColor;

D3DXHANDLE hEdgeWVP;
D3DXHANDLE hEdgeWorld;
D3DXHANDLE hEye;
D3DXHANDLE hEdgeColor;

D3DXMATRIX mtProj;
D3DXMATRIX mtView;
D3DXMATRIX mtWorld;
D3DXVECTOR3 vDirLight;
D3DXVECTOR4 cToonColor;
D3DXVECTOR4 cEdgeColor;
D3DXVECTOR3 vEye;

struct Vertex
{
	D3DXVECTOR3 positon;
	D3DXVECTOR3 normal;
};

struct EdgeVertex
{
	D3DXVECTOR3 positon;
	D3DXVECTOR3 normal;
	D3DXVECTOR3 faceNormal1;
	D3DXVECTOR3 faceNormal2;
};

struct Edge
{
	WORD meshIndex1;
	WORD meshIndex2;
	WORD edgeIndices[6];

	
};
/*
bool operator==(const Edge& lhs, const Edge& rhs)
{
	return	false;// ((rhs.meshIndex1 == lhs.meshIndex1) && (rhs.meshIndex2 == lhs.meshIndex2)) || ((rhs.meshIndex1 == lhs.meshIndex2) && (rhs.meshIndex2 == lhs.meshIndex1));
}
bool operator!=(const Edge& lhs, const Edge& rhs)
{
	return !(lhs == rhs);
}*/
bool operator<(const Edge& lhs, const Edge& rhs)
{
	//return lhs.meshIndex1 < rhs.meshIndex1;
	return (lhs.meshIndex1 + lhs.meshIndex2 < rhs.meshIndex1 + rhs.meshIndex2) && (lhs.meshIndex1 < rhs.meshIndex1);
}

bool ComputeEdge(ID3DXMesh* pMesh,IDirect3DVertexBuffer9** ppEdges, IDirect3DIndexBuffer9** ppIndices)
{
	DWORD numFaces = pMesh->GetNumFaces();
	DWORD numVertices = pMesh->GetNumVertices();
	numEdgeVertices = numVertices * 2;
	//std::stringstream log;
	struct Vertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
	};
	struct EdgeVertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		D3DXVECTOR3 faceNormal1;
		D3DXVECTOR3 faceNormal2;
	};
	Vertex* v; EdgeVertex* edgeVertex;
	IDirect3DVertexBuffer9 *pVB;
	Device->CreateVertexBuffer(
		numVertices*sizeof(EdgeVertex) * 2,
		D3DUSAGE_WRITEONLY, 
		D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX2 | D3DFVF_TEXCOORDSIZE3(0) | D3DFVF_TEXCOORDSIZE3(1),
		D3DPOOL_MANAGED,
		&pVB,
		NULL
		);
	if (SUCCEEDED(pMesh->LockVertexBuffer(0, (VOID**)&v)))
	{
		if (SUCCEEDED(pVB->Lock(0, numVertices*2*sizeof(EdgeVertex), (VOID**)&edgeVertex, 0)))
		{
			WORD* indices;
			
			pMesh->LockIndexBuffer(0, (VOID**)&indices);
			for (DWORD f = 0; f < numFaces; ++f)
			{
				std::stringstream log;
				log << "face:" << f << "\n";
				WORD index1 = indices[3 * f];
				WORD index2 = indices[3 * f + 1];
				WORD index3 = indices[3 * f + 2];
				log << "Indices:" << index1 << " " << index2 << " " << index3 << "\n";
				//OutputDebugStringA(log.str().c_str());
				D3DXVECTOR3 position1 = (v + index1)->position;
				D3DXVECTOR3 position2 = (v + index2)->position;
				D3DXVECTOR3 position3 = (v + index3)->position;
				D3DXVECTOR3 faceNormal;
				D3DXVec3Cross(&faceNormal, &(position2 - position1), &(position3 - position2));
				D3DXVec3Normalize(&faceNormal, &faceNormal);

				WORD temp[3] = { index1, index2, index3 };
				for (WORD i = 0 ; i < 3; ++i)
				{
					WORD index = temp[i];
					EdgeVertex* eV1 = (edgeVertex + index * 2);
					EdgeVertex* eV2 = (edgeVertex + index * 2 + 1);
					if (eV1->normal.x == 0 && eV1->normal.y == 0 && eV1->normal.z == 0)
					{
						eV1->position = (v + index)->position;
						eV1->normal = (v + index)->normal;
						eV1->faceNormal1 = faceNormal;
						eV1->faceNormal2 = -faceNormal;

						eV2->position = (v + index)->position;
						eV2->normal = { 0.0f, 0.0f, 0.0f };
						eV2->faceNormal1 = faceNormal;
						eV2->faceNormal2 = -faceNormal;
					}
					else
					{
						eV1->faceNormal2 = eV2->faceNormal2 = faceNormal;
					}
				}
				//OutputDebugStringA(log.str().c_str());
			}
			pMesh->UnlockIndexBuffer();
			pVB->Unlock();
		}
		pMesh->UnlockVertexBuffer();
	}
	
	WORD* meshStartIndex,*edgeStartIndex;
	std::set<Edge> edges;
	if (SUCCEEDED(pMesh->LockIndexBuffer(0, (VOID**)&meshStartIndex)))
	{
		
		
		for (DWORD i = 0; i < numFaces; ++i)
		{
			std::stringstream log;
			log << "face:" << i << "\n";
			WORD faceIndex0 = *(meshStartIndex + i * 3);
			WORD faceIndex1 = *(meshStartIndex + i * 3 + 1);
			WORD faceIndex2 = *(meshStartIndex + i * 3 + 2);
			log << "Indices:" << faceIndex0 << " " << faceIndex1 << " " << faceIndex2 << "\n";
			WORD edgeIndex0 = faceIndex0 * 2;
			WORD edgeIndex1 = faceIndex0 * 2 + 1;
			WORD edgeIndex2 = faceIndex1 * 2;
			WORD edgeIndex3 = faceIndex1 * 2 + 1;
			WORD edgeIndex4 = faceIndex2 * 2;
			WORD edgeIndex5 = faceIndex2 * 2 + 1;
			log << "EdgeIndex:" << edgeIndex0 << " " << edgeIndex1 << " " << edgeIndex2 << " " << edgeIndex3 << " " << edgeIndex4 << " " << edgeIndex5 << "\n";
			//std::stringstream log;
			Edge e;
			{
				e.meshIndex1 = faceIndex0;
				e.meshIndex2 = faceIndex1;
				WORD temp[6] = { edgeIndex0, edgeIndex2, edgeIndex3, edgeIndex3, edgeIndex1, edgeIndex0 };
				memcpy(e.edgeIndices, temp, sizeof(temp));
				edges.insert(e);
				//log << "Edge:" << e.meshIndex1 << " " << e.meshIndex2 << "\n";
			}
			{
				e.meshIndex1 = faceIndex1;
				e.meshIndex2 = faceIndex2;
				WORD temp[6] = { edgeIndex2, edgeIndex4, edgeIndex5, edgeIndex5, edgeIndex3, edgeIndex2 };
				memcpy(e.edgeIndices, temp, sizeof(temp));
				edges.insert(e);
				//log << "Edge:" << e.meshIndex1 << " " << e.meshIndex2 << "\n";
			}
			{
				e.meshIndex1 = faceIndex2;
				e.meshIndex2 = faceIndex0;
				WORD temp[6] = { edgeIndex4, edgeIndex0, edgeIndex1, edgeIndex1, edgeIndex5, edgeIndex4 };
				memcpy(e.edgeIndices, temp, sizeof(temp));
				edges.insert(e);
				//log << "Edge:" << e.meshIndex1 << " " << e.meshIndex2 << "\n";
			}
			//OutputDebugStringA(log.str().c_str());
		}
		pMesh->UnlockIndexBuffer();
		
	}
	numEdges = edges.size() * 2;
	IDirect3DIndexBuffer9* pIB;
	Device->CreateIndexBuffer(edges.size() * 6 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&pIB,
		NULL);
	if (SUCCEEDED(pIB->Lock(0, edges.size() * 6 * sizeof(WORD), (VOID**)&edgeStartIndex, 0)))
	{
		
		for (std::set<Edge>::iterator it = edges.begin(); it != edges.end(); ++it)
		{
			std::stringstream log;
			log << "Edge:" << it->meshIndex1 << " " << it->meshIndex2 << "\n";
			memcpy(edgeStartIndex, it->edgeIndices, sizeof(it->edgeIndices));
			edgeStartIndex += 6;
			//OutputDebugStringA(log.str().c_str());
		}
		
		pIB->Unlock();
	}
	if (SUCCEEDED(pIB->Lock(0, edges.size() * 6 * sizeof(WORD), (VOID**)&edgeStartIndex, 0)))
	{
		for (UINT i = 0; i < edges.size() * 6; ++i)
		{
			std::stringstream log;
			log << "Index:" << *edgeStartIndex++ << "\n";
			//OutputDebugStringA(log.str().c_str());
		}
		pIB->Unlock();
	}
	if (SUCCEEDED(pVB->Lock(0, numEdgeVertices * sizeof(EdgeVertex), (VOID**)&edgeVertex, 0)))
	{
		for (UINT i = 0; i < numEdgeVertices; ++i)
		{
			std::stringstream log;
			log << "i:" << i << "\n";
			log << "position:" << (edgeVertex + i)->position.x << " " << (edgeVertex + i)->position.y << " " << (edgeVertex + i)->position.z << "\n";
			log << "normal:" << (edgeVertex + i)->normal.x << " " << (edgeVertex + i)->normal.y << " " << (edgeVertex + i)->normal.z << "\n";
			log << "faceNormal1:" << (edgeVertex + i)->faceNormal1.x << " " << (edgeVertex + i)->faceNormal1.y << " " << (edgeVertex + i)->faceNormal1.z << "\n";
			log << "faceNormal2:" << (edgeVertex + i)->faceNormal2.x << " " << (edgeVertex + i)->faceNormal2.y << " " << (edgeVertex + i)->faceNormal2.z << "\n";
			OutputDebugStringA(log.str().c_str());
		}
		pIB->Unlock();
	}
	*ppEdges = pVB;
	*ppIndices = pIB;
	return true;
}

bool Setup()
{
	HRESULT hr;
	D3DXCreateTeapot(Device, &pMesh, NULL);
	ComputeEdge(pMesh, &pEdges, &pEdgeIndices);
	hr = D3DXCreateTextureFromFile(Device, L"bright.bmp", &pBrightTexture);
	D3DVERTEXELEMENT9 toonElems[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		D3DDECL_END()
	};
	hr = Device->CreateVertexDeclaration(toonElems, &pToonDecl);
	D3DVERTEXELEMENT9 edgeElems[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 1 },
		{ 0, 36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 2 },
		D3DDECL_END()
	};
	hr = Device->CreateVertexDeclaration(edgeElems, &pEdgeDecl);
	ID3DXBuffer* pShader, *pError;
	
	hr = D3DXCompileShaderFromFile(L"toon.txt", NULL, NULL, "Main", "vs_2_0", D3DXSHADER_DEBUG | D3DXSHADER_SKIPOPTIMIZATION, &pShader, &pError, &pToonConst);
	if (FAILED(hr))
	{
		OutputDebugStringA((char*)pError->GetBufferPointer());
		return false;
	}
	hToonWVP = pToonConst->GetConstantByName(0, "WorldViewProj");
	hToonWorld = pToonConst->GetConstantByName(0, "World");
	hDirLight = pToonConst->GetConstantByName(0, "DirLight");
	hToonColor = pToonConst->GetConstantByName(0, "Color");

	Device->CreateVertexShader((DWORD*)pShader->GetBufferPointer(), &pToonSH);
	hr = D3DXCompileShaderFromFile(L"outline.txt", NULL, NULL, "Main", "vs_2_0", D3DXSHADER_DEBUG | D3DXSHADER_SKIPOPTIMIZATION, &pShader, &pError, &pEdgeConst);
	if (FAILED(hr))
	{
		OutputDebugStringA((char*)pError->GetBufferPointer());
		return false;
	}
	hEdgeWVP = pEdgeConst->GetConstantByName(0, "WorldViewProj");
	hEdgeWorld = pEdgeConst->GetConstantByName(0, "World");
	hEye = pEdgeConst->GetConstantByName(0, "EyePosition");
	hEdgeColor = pEdgeConst->GetConstantByName(0, "Color");

	Device->CreateVertexShader((DWORD*)pShader->GetBufferPointer(), &pEdgeSH);

	D3DXMatrixPerspectiveFovLH(&mtProj, D3DX_PI*0.2, float(Width) / Height, 1.0f, 1000.0f);

	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 eye(0.0f, 0.0f, -10.0f);
	D3DXMatrixLookAtLH(&mtView, &eye, &target, &up);

	D3DXMatrixIdentity(&mtWorld);

	pEdgeConst->SetFloatArray(Device, hEye, eye, 3);

	D3DXVECTOR3 DirLight(1.0f, 0.0f, 0.0f);

	pToonConst->SetFloatArray(Device, hDirLight, DirLight, 3);
	D3DXVECTOR4 toonColor(0.3f, 0.6f, 0.7f, 1.0f);
	pToonConst->SetVector(Device, hToonColor, &toonColor);
	D3DXVECTOR4 edgeColor(0.0f, 0.0f, 0.0f, 0.0f);
	pEdgeConst->SetVector(Device, hEdgeColor, &edgeColor);

	Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	Device->SetRenderState(D3DRS_ZENABLE, TRUE);
	Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	Device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	return true;
}

void Cleanup()
{

}

bool Display(float timeDelta)
{
	Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
	D3DXMATRIX Ry;
	D3DXMatrixRotationY(&Ry, 0.0001f);
	D3DXMatrixMultiply(&mtWorld, &mtWorld, &Ry);
	
	if (SUCCEEDED(Device->BeginScene()))
	{
		pToonConst->SetMatrix(Device, hToonWVP, &(mtWorld*mtView*mtProj));
		pToonConst->SetMatrix(Device, hToonWorld, &mtWorld);
		Device->SetVertexShader(pToonSH);
		Device->SetVertexDeclaration(pToonDecl);
		Device->SetTexture(0, pBrightTexture);
		pMesh->DrawSubset(0);

		pEdgeConst->SetMatrix(Device, hEdgeWorld, &mtWorld);
		pEdgeConst->SetMatrix(Device, hEdgeWVP, &(mtWorld*mtView*mtProj));
		Device->SetVertexShader(pEdgeSH);
		Device->SetVertexDeclaration(pEdgeDecl);
		Device->SetTexture(0, 0);
		Device->SetStreamSource(0, pEdges, 0, sizeof(EdgeVertex));
		Device->SetIndices(pEdgeIndices);
		Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, numEdgeVertices, 0, numEdges);
		Device->EndScene();
	}
	Device->Present(0,0,0,0);
	return true;
}

