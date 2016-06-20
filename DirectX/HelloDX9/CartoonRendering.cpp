#include "Demo.h"
IDirect3DDevice9* Device;
ID3DXMesh* pMesh;
IDirect3DVertexBuffer9* pEdges;
IDirect3DIndexBuffer9* pEdgeIndices;

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


bool ComputeEdge(ID3DXMesh* pMesh,IDirect3DVertexBuffer9** ppEdges, IDirect3DIndexBuffer9** pIndices)
{
	DWORD numFaces = pMesh->GetNumFaces();
	DWORD numVertices = pMesh->GetNumVertices();
	IDirect3DDevice9* pDevice; 
	if (FAILED(pMesh->GetDevice(&pDevice)))
	{
		return false;
	}
	IDirect3DVertexBuffer9* pEdges;
	pDevice->CreateVertexBuffer(numVertices*sizeof()

	Vertex* v;
	if (SUCCEEDED(pMesh->LockVertexBuffer(0, (VOID**)&v)))
	{
		for (DWORD f = 0; f < numFaces; ++f)
		{
			DWORD index1 = f;
			DWORD index2 = 3 * f + 1;
			DWORD index3 = 3 * f + 2;

			D3DXVECTOR3 positon1 = (v + 3 * index1)->positon;
			D3DXVECTOR3 positon2 = (v + 3 * index2)->positon;
			D3DXVECTOR3 positon3 = (v + 3 * index3)->positon;

			D3DXVECTOR3 normal;
			D3DXVec3Cross(&normal, &(positon2 - positon1), &(positon3 - positon2));
			D3DXVec3Normalize(&normal, &normal);

			DWORD adj1 = Adjs[f];
			DWORD adj2 = Adjs[3 * f + 1];
			DWORD adj3 = Adjs[3 * f + 2];

			DWORD adjs[3] = { adj1, adj2, adj3 };
			D3DXVECTOR3 normals[3];
			for (int i = 0; i < 3;++i)
			{
				if (adjs[i] == -1) continue;
				D3DXVECTOR3 positon1 = (v + 3 * adjs[i])->positon;
				D3DXVECTOR3 positon2 = (v + 3 * adjs[i] + 1)->positon;
				D3DXVECTOR3 positon3 = (v + 3 * adjs[i] + 2)->positon;
				D3DXVECTOR3 normal;
				D3DXVec3Cross(&normals[i], &(positon2 - positon1), &(positon3 - positon2));
				D3DXVec3Normalize(&normals[i], &normals[i]);
			}
		}
	}
	delete[] Adjs;
}

bool Setup()
{
	return true;
}

void Cleanup()
{

}

bool Display(float timeDelta)
{

}

