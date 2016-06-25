#include "Demo.h"
#include <set>
#include <unordered_map>
#include <sstream>
#include <functional>

IDirect3DDevice9* Device;
ID3DXMesh* pMesh;
IDirect3DVertexBuffer9* pEdges;
IDirect3DIndexBuffer9* pEdgeIndices;
IDirect3DTexture9* pBrightTexture;
IDirect3DVertexShader9* pToonSH;
ID3DXConstantTable* pToonConst;
IDirect3DVertexShader9* pEdgeSH;
ID3DXConstantTable* pEdgeConst;
IDirect3DVertexShader9* pFaceNormalSH;
ID3DXConstantTable* pFaceNormalConst;
IDirect3DVertexDeclaration9* pToonDecl;
IDirect3DVertexDeclaration9* pEdgeDecl;
IDirect3DVertexDeclaration9* pFaceNormalDecl;
DWORD numEdgeVertices;
DWORD numEdgePrims;

IDirect3DVertexBuffer9* pFaceNormals;
IDirect3DIndexBuffer9* pFaceNormalIndices;

D3DXHANDLE hToonWVP;
D3DXHANDLE hToonWorld;
D3DXHANDLE hDirLight;
D3DXHANDLE hToonColor;

D3DXHANDLE hEdgeWVP;
D3DXHANDLE hEdgeWorld;
D3DXHANDLE hEye;
D3DXHANDLE hEdgeColor;

D3DXHANDLE hFaceNormalWVP;

D3DXMATRIX mtProj;
D3DXMATRIX mtView;
D3DXMATRIX mtWorld;
D3DXVECTOR3 vDirLight;
D3DXVECTOR4 cToonColor;
D3DXVECTOR4 cEdgeColor;
D3DXVECTOR3 vEye;

struct SimpleVertex
{
	D3DXVECTOR3 positon;
};

struct Vertex
{
	D3DXVECTOR3 positon;
	D3DXVECTOR3 normal;
};

struct EdgeVertex
{
	D3DXVECTOR3 position;
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

bool operator<(const Edge& lhs, const Edge& rhs)
{
	return (lhs.meshIndex1 + lhs.meshIndex2 < rhs.meshIndex1 + rhs.meshIndex2) && ((lhs.meshIndex1 < rhs.meshIndex1) || (lhs.meshIndex2 < rhs.meshIndex2));
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
				D3DXVec3Cross(&faceNormal, &(position1 - position2), &(position2 - position3));
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
			WORD faceIndex0 =  meshStartIndex[i * 3];
			WORD faceIndex1 =  meshStartIndex[i * 3 + 1];
			WORD faceIndex2 =  meshStartIndex[i * 3 + 2];
			log << "Indices:" << faceIndex0 << " " << faceIndex1 << " " << faceIndex2 << "\n";
			WORD edgeIndex0 = faceIndex0 * 2;
			WORD edgeIndex1 = faceIndex0 * 2 + 1;
			WORD edgeIndex2 = faceIndex1 * 2;
			WORD edgeIndex3 = faceIndex1 * 2 + 1;
			WORD edgeIndex4 = faceIndex2 * 2;
			WORD edgeIndex5 = faceIndex2 * 2 + 1;
			log << "EdgeIndex:" << edgeIndex0 << " " << edgeIndex1 << " " << edgeIndex2 << " " << edgeIndex3 << " " << edgeIndex4 << " " << edgeIndex5 << "\n";
			//std::stringstream log;
			
			{
				Edge e;
				e.meshIndex1 = faceIndex0;
				e.meshIndex2 = faceIndex1;
				WORD temp[6] = { edgeIndex0, edgeIndex2, edgeIndex3, edgeIndex3, edgeIndex1, edgeIndex0 };
				memcpy(e.edgeIndices, temp, sizeof(temp));
				edges.insert(e);
				//log << "Edge:" << e.meshIndex1 << " " << e.meshIndex2 << "\n";
			}
			{
				Edge e;
				e.meshIndex1 = faceIndex1;
				e.meshIndex2 = faceIndex2;
				WORD temp[6] = { edgeIndex2, edgeIndex4, edgeIndex5, edgeIndex5, edgeIndex3, edgeIndex2 };
				memcpy(e.edgeIndices, temp, sizeof(temp));
				edges.insert(e);
				//log << "Edge:" << e.meshIndex1 << " " << e.meshIndex2 << "\n";
			}
			{
				Edge e;
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
	numEdgePrims = edges.size() * 2;
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

struct MeshEdge
{
	WORD meshIndex1;
	WORD meshIndex2;
	D3DXVECTOR3 position1;
	D3DXVECTOR3 position2;
	D3DXVECTOR3 normal1;
	D3DXVECTOR3 normal2;
	D3DXVECTOR3 faceNormal1;
	D3DXVECTOR3 faceNormal2;
};

bool operator==(const MeshEdge& lhs, const MeshEdge& rhs)
{
	return lhs.meshIndex1 == rhs.meshIndex1 && lhs.meshIndex2 == rhs.meshIndex2 || lhs.meshIndex1 == rhs.meshIndex2 && lhs.meshIndex2 == rhs.meshIndex1;
}

struct MeshEdgeHash
{
	size_t operator()(const MeshEdge& m)
	{
		return std::hash<WORD>()(m.meshIndex1) ^ std::hash<WORD>()(m.meshIndex2);
	}
};


bool ComputeEdge2(ID3DXMesh* pMesh, IDirect3DVertexBuffer9** ppEdges, IDirect3DIndexBuffer9** ppIndices, IDirect3DVertexBuffer9** ppFaceNoramls, IDirect3DIndexBuffer9** ppFaceNoramlIndices)
{
	DWORD numFaces = pMesh->GetNumFaces();
	Vertex* meshVertex;
	WORD* indeices;
	//std::set<MeshEdge> meshEdges;
	typedef std::unordered_map<MeshEdge, MeshEdge, MeshEdgeHash> MeshEdgeHashMap;
	MeshEdgeHashMap meshEdges;
	if (SUCCEEDED(pMesh->LockVertexBuffer(0, (VOID**)&meshVertex)))
	{
		if (SUCCEEDED(pMesh->LockIndexBuffer(0, (VOID**)&indeices)))
		{
			for (DWORD f = 0; f < numFaces; ++f)
			{
				std::stringstream log;
				log << "Face:" << f << "\n";
				WORD index1 = indeices[f * 3];
				WORD index2 = indeices[f * 3 + 1];
				WORD index3 = indeices[f * 3 + 2];
				Vertex vertex1 = meshVertex[index1];
				Vertex vertex2 = meshVertex[index2];
				Vertex vertex3 = meshVertex[index3];
				D3DXVECTOR3 normal = vertex1.normal + vertex2.normal + vertex3.normal;
				//D3DXVec3Cross(&normal, &(vertex2.positon - vertex1.positon), &(vertex2.positon - vertex3.positon));
				D3DXVec3Normalize(&normal, &normal);
				log << "Normal:" << normal.x << " " << normal.y << " " << normal.z << "\n";
				//OutputDebugStringA(log.str().c_str());
				{
					MeshEdge edge;
					edge.meshIndex1 = index1;
					edge.meshIndex2 = index2;
					edge.position1 = vertex1.positon;
					edge.position2 = vertex2.positon;
					edge.normal1 = vertex1.normal;
					edge.normal2 = vertex2.normal;
					MeshEdgeHashMap::iterator edgeFind = meshEdges.find(edge);
					if (edgeFind != meshEdges.end())
					{
						edge = edgeFind->first;
						edge.faceNormal2 = normal;
					}
					else
					{
						edge.faceNormal1 = normal;
						edge.faceNormal2 = -normal;
						
					}
					meshEdges[edge] = edge;
				}
				{
					MeshEdge edge;
					edge.meshIndex1 = index2;
					edge.meshIndex2 = index3;
					edge.position1 = vertex2.positon;
					edge.position2 = vertex3.positon;
					edge.normal1 = vertex2.normal;
					edge.normal2 = vertex3.normal;
					MeshEdgeHashMap::iterator edgeFind = meshEdges.find(edge);
					if (edgeFind != meshEdges.end())
					{
						edge = edgeFind->first;
						edge.faceNormal2 = normal;
					}
					else
					{
						edge.faceNormal1 = normal;
						edge.faceNormal2 =  -normal;
					}
					meshEdges[edge] = edge;
				}
				{
					MeshEdge edge;
					edge.meshIndex1 = index3;
					edge.meshIndex2 = index1;
					edge.position1 = vertex3.positon;
					edge.position2 = vertex1.positon;
					edge.normal1 = vertex3.normal;
					edge.normal2 = vertex1.normal;
					MeshEdgeHashMap::iterator edgeFind = meshEdges.find(edge);
					if (edgeFind != meshEdges.end())
					{
						edge = edgeFind->first;
						edge.faceNormal2 = normal;
					}
					else
					{
						edge.faceNormal1 = normal;
						edge.faceNormal2 = -normal;
					}
					meshEdges[edge] = edge;
				}
			}
			pMesh->UnlockIndexBuffer();
		}
		pMesh->UnlockVertexBuffer();
	}

	DWORD numEdges = meshEdges.size();

	IDirect3DVertexBuffer9* pVB;
	IDirect3DIndexBuffer9* pIB;
	Device->CreateVertexBuffer(
		numEdges * 4 * sizeof(EdgeVertex),
		D3DUSAGE_WRITEONLY,
		D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX2 | D3DFVF_TEXCOORDSIZE3(0) | D3DFVF_TEXCOORDSIZE3(1),
		D3DPOOL_MANAGED,
		&pVB,
		NULL);
	Device->CreateIndexBuffer(
		numEdges * 6 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&pIB,
		NULL);
	IDirect3DVertexBuffer9* pVBFaceNormal;
	IDirect3DIndexBuffer9* pIBFaceNormal;
	Device->CreateVertexBuffer(
		numEdges * 8 * sizeof(SimpleVertex),
		D3DUSAGE_WRITEONLY,
		D3DFVF_XYZ | D3DFVF_NORMAL,
		D3DPOOL_MANAGED,
		&pVBFaceNormal,
		NULL);
	Device->CreateIndexBuffer(
		numEdges * 8 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&pIBFaceNormal,
		NULL);
	EdgeVertex* eVertices;
	WORD* eIndices;
	SimpleVertex* fnVertices;
	WORD* fnIndices;
	pVB->Lock(0, numEdges * 4 * sizeof(EdgeVertex), (VOID**)&eVertices, 0);
	pIB->Lock(0, numEdges * 6 * sizeof(WORD), (VOID**)&eIndices, 0);
	pVBFaceNormal->Lock(0, numEdges * 8 * sizeof(SimpleVertex), (VOID**)&fnVertices, 0);
	pIBFaceNormal->Lock(0, numEdges * 8 * sizeof(WORD), (VOID**)&fnIndices, 0);
	WORD offset = 0;
	for (MeshEdgeHashMap::iterator it = meshEdges.begin(); it != meshEdges.end(); ++it)
	{
		MeshEdge edge = it->second;
		eVertices->position = edge.position1;
		eVertices->normal = edge.normal1;
		eVertices->faceNormal1 = edge.faceNormal1;
		eVertices->faceNormal2 = edge.faceNormal2;

		D3DXVECTOR3 pos1 = (edge.position1 + edge.position2) / 2 + (edge.position1 - edge.position2) * 0.2f;
		D3DXVECTOR3 pos2 = (edge.position1 + edge.position2) / 2 + (edge.position2 - edge.position1) * 0.2f;
		fnVertices->positon = pos1;
		fnVertices++;
		fnVertices->positon = pos1 + edge.faceNormal1*.2f;
		fnVertices++;
		fnVertices->positon = pos2;
		fnVertices++;
		fnVertices->positon = pos2 + edge.faceNormal2*.2f;
		fnVertices++;

		eVertices++;

		eVertices->position = edge.position1;
		eVertices->normal = { 0.0f, 0.0f, 0.0f };
		eVertices->faceNormal1 = edge.faceNormal1;
		eVertices->faceNormal2 = edge.faceNormal2;
		eVertices++;

		eVertices->position = edge.position2;
		eVertices->normal = edge.normal2;
		eVertices->faceNormal1 = edge.faceNormal1;
		eVertices->faceNormal2 = edge.faceNormal2;

		pos1 = (edge.position1 + edge.position2) / 2 + (edge.position1 - edge.position2) * 0.2f;
		pos2 = (edge.position1 + edge.position2) / 2 + (edge.position2 - edge.position1) * 0.2f;

		fnVertices->positon = pos1;
		fnVertices++;
		fnVertices->positon = pos1 + edge.faceNormal1 *.2f;
		fnVertices++;
		fnVertices->positon = pos2;
		fnVertices++;
		fnVertices->positon = pos2 + edge.faceNormal2*.2f;
		fnVertices++;

		eVertices++;

		eVertices->position = edge.position2;
		eVertices->normal = { 0.0f, 0.0f, 0.0f };
		eVertices->faceNormal1 = edge.faceNormal1;
		eVertices->faceNormal2 = edge.faceNormal2;
		eVertices++;
		WORD temp[] = { offset + 0, offset + 2, offset + 3, offset + 3, offset + 1, offset + 0 };
		WORD temp2[] = { 2 * offset + 0, 2 * offset + 1, 2 * offset + 2, 2 * offset + 3, 2 * offset + 4, 2 * offset + 5, 2 * offset + 6, 2 * offset + 7 };
		memcpy(eIndices, temp, sizeof(temp));
		memcpy(fnIndices, temp2, sizeof temp2);
		offset += 4;
		eIndices += 6;
		fnIndices += 8;
	}
	
	numEdgeVertices = numEdges * 4;
	numEdgePrims = numEdges * 2;
	pVBFaceNormal->Unlock();
	pIB->Unlock();
	pVB->Unlock();
	*ppEdges = pVB;
	*ppIndices = pIB;
	*ppFaceNoramls = pVBFaceNormal;
	*ppFaceNoramlIndices = pIBFaceNormal;
	if (SUCCEEDED(pIB->Lock(0, numEdges * 6 * sizeof(WORD), (VOID**)&eIndices, 0)))
	{
		for (UINT i = 0; i < numEdges * 6; ++i)
		{
			std::stringstream log;
			log << "Index:" << *eIndices++ << "\n";
			//OutputDebugStringA(log.str().c_str());
		}
		pIB->Unlock();
	}
	if (SUCCEEDED(pVB->Lock(0, numEdges * 4 * sizeof(EdgeVertex), (VOID**)&eVertices, 0)))
	{
		for (UINT i = 0; i < numEdges*4; ++i)
		{
			std::stringstream log;
			log << "i:" << i << "\n";
			log << "position:" << (eVertices + i)->position.x << " " << (eVertices + i)->position.y << " " << (eVertices + i)->position.z << "\n";
			log << "normal:" << (eVertices + i)->normal.x << " " << (eVertices + i)->normal.y << " " << (eVertices + i)->normal.z << "\n";
			log << "faceNormal1:" << (eVertices + i)->faceNormal1.x << " " << (eVertices + i)->faceNormal1.y << " " << (eVertices + i)->faceNormal1.z << "\n";
			log << "faceNormal2:" << (eVertices + i)->faceNormal2.x << " " << (eVertices + i)->faceNormal2.y << " " << (eVertices + i)->faceNormal2.z << "\n";
			//OutputDebugStringA(log.str().c_str());
		}
		pIB->Unlock();
	}
	return true;
}

bool Setup()
{
	HRESULT hr;

	D3DVIEWPORT9 viewport = { 0, 0, Width, Height };
	Device->SetViewport(&viewport);

	D3DXCreateTeapot(Device, &pMesh, NULL);
	//D3DXCreateSphere(Device, 1.0f, 10, 10, &pMesh, NULL);
	//D3DXCreatePolygon(Device, 1.0f, 4, &pMesh, NULL);
	ComputeEdge2(pMesh, &pEdges, &pEdgeIndices, &pFaceNormals,&pFaceNormalIndices);
	hr = D3DXCreateTextureFromFile(Device, L"brightness.bmp", &pBrightTexture);
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
	D3DVERTEXELEMENT9 fnElems[] =
	{
		{ 0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
		D3DDECL_END()
	};
	hr = Device->CreateVertexDeclaration(fnElems, &pFaceNormalDecl);
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
	hEdgeWVP = pEdgeConst->GetConstantByName(0, "ViewProj");
	hEdgeWorld = pEdgeConst->GetConstantByName(0, "World");
	hEye = pEdgeConst->GetConstantByName(0, "Eye");
	hEdgeColor = pEdgeConst->GetConstantByName(0, "Color");

	Device->CreateVertexShader((DWORD*)pShader->GetBufferPointer(), &pEdgeSH);

	hr = D3DXCompileShaderFromFile(L"line.txt", NULL, NULL, "Main", "vs_2_0", D3DXSHADER_DEBUG | D3DXSHADER_SKIPOPTIMIZATION, &pShader, &pError, &pFaceNormalConst);
	if (FAILED(hr))
	{
		OutputDebugStringA((char*)pError->GetBufferPointer());
		return false;
	}
	hFaceNormalWVP = pFaceNormalConst->GetConstantByName(0, "WorldViewProj");

	Device->CreateVertexShader((DWORD*)pShader->GetBufferPointer(), &pFaceNormalSH);

	D3DXMatrixPerspectiveFovLH(&mtProj, D3DX_PI*0.2, float(Width) / Height, 1.0f, 1000.0f);

	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 eye(1.00f, 1.00f, 3.50f);
	D3DXMatrixLookAtLH(&mtView, &eye, &target, &up);

	D3DXMatrixIdentity(&mtWorld);

	pEdgeConst->SetFloatArray(Device, hEye, eye, 3);

	D3DXVECTOR3 DirLight(-1.0f, 0.0f, 0.0f);

	pToonConst->SetFloatArray(Device, hDirLight, DirLight, 3);
	D3DXVECTOR4 toonColor(0.1f, 0.2f, 0.4f, 1.0f);
	pToonConst->SetVector(Device, hToonColor, &toonColor);
	D3DXVECTOR4 edgeColor(1.0f, 0.0f, 0.0f, 0.0f);
	pEdgeConst->SetVector(Device, hEdgeColor, &edgeColor);
	
	
	Device->SetRenderState(D3DRS_ZENABLE, TRUE);
	
	return true;
}

void Cleanup()
{

}

bool Display(float timeDelta)
{
	Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
	D3DXMATRIX Ry;
	D3DXMatrixRotationY(&Ry, 0.00001f);
	D3DXMatrixMultiply(&mtWorld, &mtWorld, &Ry);
	
	if (SUCCEEDED(Device->BeginScene()))
	{
		D3DXVECTOR3 DirLight(-1.0f, 0.0f, 0.0f);

		pToonConst->SetFloatArray(Device, hDirLight, DirLight, 3);
		D3DXVECTOR4 toonColor(0.1f, 0.2f, 0.4f, 1.0f);
		pToonConst->SetVector(Device, hToonColor, &toonColor);
		D3DXVECTOR4 edgeColor(1.0f, 0.0f, 0.0f, 0.0f);
		pEdgeConst->SetVector(Device, hEdgeColor, &edgeColor);
		Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		Device->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
		pToonConst->SetMatrix(Device, hToonWVP, &(mtWorld*mtView*mtProj));
		pToonConst->SetMatrix(Device, hToonWorld, &mtWorld);
		Device->SetVertexDeclaration(pToonDecl);
		Device->SetVertexShader(pToonSH);
		Device->SetTexture(0, pBrightTexture);
		//Device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		pMesh->DrawSubset(0);

		
		D3DXVECTOR3 eye(1.00f, 1.00f, 3.50f);
		pEdgeConst->SetFloatArray(Device, hEye, eye, 3);
		Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);
		pEdgeConst->SetMatrix(Device, hEdgeWorld, &mtWorld);
		pEdgeConst->SetMatrix(Device, hEdgeWVP, &(mtView*mtProj));
		Device->SetVertexShader(pEdgeSH);
		Device->SetVertexDeclaration(pEdgeDecl);
		Device->SetTexture(0, 0);
		Device->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
		Device->SetStreamSource(0, pEdges, 0, sizeof(EdgeVertex));
		Device->SetIndices(pEdgeIndices);
		Device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, numEdgeVertices, 0, numEdgePrims);
		
		/*
		pFaceNormalConst->SetMatrix(Device, hFaceNormalWVP, &(mtWorld*mtView*mtProj));
		Device->SetVertexShader(pFaceNormalSH);
		Device->SetVertexDeclaration(pFaceNormalDecl);
		Device->SetStreamSource(0, pFaceNormals, 0, sizeof(SimpleVertex));
		Device->SetIndices(pFaceNormalIndices);
		Device->DrawIndexedPrimitive(D3DPT_LINELIST, 0, 0, numEdgeVertices * 2, 0, numEdgeVertices * 2);
		*/
		Device->EndScene();
		
	}
	Device->Present(0,0,0,0);
	return true;
}

