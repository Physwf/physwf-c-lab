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
bool operator==(const Edge& lhs, const Edge& rhs)
{
	return	(rhs.meshIndex1 == lhs.meshIndex1 && rhs.meshIndex2 == lhs.meshIndex2) ||
		(rhs.meshIndex1 == lhs.meshIndex2 && rhs.meshIndex2 == lhs.meshIndex1);
}
bool operator!=(const Edge& lhs, const Edge& rhs)
{
	return !(lhs == rhs);
}
bool operator<(const Edge& lhs, const Edge& rhs)
{
	return lhs.meshIndex1 < rhs.meshIndex1;
}

bool ComputeEdge(ID3DXMesh* pMesh,IDirect3DVertexBuffer9** ppEdges, IDirect3DIndexBuffer9** ppIndices)
{
	DWORD numFaces = pMesh->GetNumFaces();
	DWORD numVertices = pMesh->GetNumVertices();
	numEdgeVertices = numVertices * 2;
	std::stringstream log;
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
				log << "face:" << f << "\n";
				DWORD index1 = indices[3 * f];
				DWORD index2 = indices[3 * f + 1];
				DWORD index3 = indices[3 * f + 2];
				//OutputDebugStringA(log.str().c_str());
				D3DXVECTOR3 position1 = (v + index1)->position;
				D3DXVECTOR3 position2 = (v + index2)->position;
				D3DXVECTOR3 position3 = (v + index3)->position;
				D3DXVECTOR3 faceNormal;
				D3DXVec3Cross(&faceNormal, &(position2 - position1), &(position3 - position2));
				D3DXVec3Normalize(&faceNormal, &faceNormal);

				for (DWORD index = index1 ; index <= index3; ++index)
				{
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
			WORD meshIndex0 = *(meshStartIndex + i * 3);
			WORD meshIndex1 = *(meshStartIndex + i * 3 + 1);
			WORD meshIndex2 = *(meshStartIndex + i * 3 + 2);

			WORD edgeIndex0 = meshIndex0 * 2;
			WORD edgeIndex1 = meshIndex0 * 2 + 1;
			WORD edgeIndex2 = meshIndex1 * 2;
			WORD edgeIndex3 = meshIndex1 * 2 + 1;
			WORD edgeIndex4 = meshIndex2 * 2;
			WORD edgeIndex5 = meshIndex2 * 2 + 1;

			Edge e;
			{
				e.meshIndex1 = meshIndex0;
				e.meshIndex2 = meshIndex1;
				WORD temp[6] = { edgeIndex0, edgeIndex2, edgeIndex3, edgeIndex3, edgeIndex1, edgeIndex0 };
				memcpy(e.edgeIndices, temp, sizeof(temp));
				edges.insert(e);
			}
			{
				e.meshIndex1 = meshIndex1;
				e.meshIndex2 = meshIndex2;
				WORD temp[6] = { edgeIndex2, edgeIndex4, edgeIndex5, edgeIndex5, edgeIndex3, edgeIndex2 };
				memcpy(e.edgeIndices, temp, sizeof(temp));
				edges.insert(e);
			}
			{
				e.meshIndex1 = meshIndex2;
				e.meshIndex2 = meshIndex0;
				WORD temp[6] = { edgeIndex4, edgeIndex0, edgeIndex1, edgeIndex1, edgeIndex5, edgeIndex4 };
				memcpy(e.edgeIndices, temp, sizeof(temp));
				edges.insert(e);
			}
			
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
			memcpy(edgeStartIndex, it->edgeIndices, sizeof(edges));
			edgeStartIndex += 6;
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
	D3DXCreateTextureFromFile(Device, L"bright.jpg", &pBrightTexture);
	D3DVERTEXELEMENT9 toonElems[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 }
	};
	Device->CreateVertexDeclaration(toonElems, &pToonDecl);
	D3DVERTEXELEMENT9 edgeElems[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0 },
		{ 0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 1 },
		{ 0, 36, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 2 }
	};
	Device->CreateVertexDeclaration(edgeElems, &pEdgeDecl);
	ID3DXBuffer* pShader, *pError;
	
	hr = D3DXCompileShaderFromFile(L"toon.tex", NULL, NULL, "Main", "vs_2_0", D3DXSHADER_DEBUG, &pShader, &pError, &pToonConst);
	if (FAILED(hr))
	{
		OutputDebugStringA((char*)pError->GetBufferPointer());
		return false;
	}
	Device->CreateVertexShader((DWORD*)pShader->GetBufferPointer(), &pToonSH);
	hr = D3DXCompileShaderFromFile(L"outline.txt", NULL, NULL, "Main", "vs_2_0", D3DXSHADER_DEBUG, &pShader, &pError, &pEdgeConst);
	if (FAILED(hr))
	{
		OutputDebugStringA((char*)pError->GetBufferPointer());
		return false;
	}
	Device->CreateVertexShader((DWORD*)pShader->GetBufferPointer(), &pEdgeSH);

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
		Device->SetVertexShader(pToonSH);
		Device->SetVertexDeclaration(pToonDecl);
		Device->SetTexture(0, pBrightTexture);
		pMesh->DrawSubset(0);

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

