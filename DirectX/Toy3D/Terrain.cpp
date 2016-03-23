#include "Terrain.h"
#include "Debuger.h"
#include <fstream>

using namespace Toy3D;

void Terrain::Initialize(const char* rawfile, const char* texfile)
{
	std::ifstream heightStream;
	heightStream.open(rawfile, std::ios::binary);
	if (heightStream.fail()) return;

	heightStream.seekg(0, std::ios::end);
	UINT numVertices = (UINT)heightStream.tellg();

	heightStream.seekg(0, std::ios::beg);
	m_spHeightMap.reset(new UCHAR[numVertices]);
	heightStream.read((char*)m_spHeightMap.get(), numVertices);
	heightStream.close();

	IDirect3DTexture9* tex;
	D3DXCreateTextureFromFile(d3dContext->GetDevice().get(), texfile, &tex);
	m_spTexture.reset(tex, [](IDirect3DTexture9* tex){tex->Release(); });

	AlllocateBuffers();
	m_bDirty = true;
	Update(0);
}

std::shared_ptr<Terrain> Terrain::Create(const TerrainDesc* desc)
{
	std::shared_ptr<Terrain> result = std::make_shared<Terrain>(desc->Width, desc->Depth, desc->Height, desc->HeightMapWidth,desc->HeightMapHeight);
	result->Initialize(desc->HeightMapPath, desc->TexturePath);
	return result;
}

void Terrain::computeVertices(TexVertex* vertices)
{
	float unitX = static_cast<float>(m_uWidth) / m_uHeightMapWidth;
	float unitZ = static_cast<float>(m_uDepth) / m_uHeightMapHeight;

	float halfX = static_cast<float>(m_uWidth) / 2;
	float halfZ = static_cast<float>(m_uDepth) / 2;

	float unitU = 1.0f / m_uHeightMapWidth;
	float unitV = 1.0f / m_uHeightMapHeight;

	UINT numVerticesX = m_uHeightMapWidth + 1;
	UINT numVerticesZ = m_uHeightMapHeight + 1;

	UINT index = 0;
	for (UINT i = 0; i < numVerticesZ; ++i)
	{
		for (UINT j = 0; j < numVerticesX; ++j)
		{
			index = i*numVerticesZ + j;
			//Debug_Trace(index);
			//Debug_Trace((int)m_spHeightMap[index]);
			vertices[index] = TexVertex(unitX*j - halfX, m_spHeightMap[index] / 255.0f * m_uHeight, halfZ -unitZ*i , j*unitU, i*unitV);
		}
	}
}

void Terrain::computeVertices(TexNormalVertex* vertices)
{

}

void Terrain::AlllocateBuffers()
{
	IDirect3DVertexBuffer9* vb;
	d3dContext->CreateVertexBuffer(
		m_uNumVertices*sizeof(TexVertex),
		D3DUSAGE_WRITEONLY,
		TexVertex::FVF_TEX,
		D3DPOOL_MANAGED,
		&vb,
		0);
	m_spVetexBuffer.reset(vb, [](IDirect3DVertexBuffer9* vb) {vb->Release(); });

	IDirect3DIndexBuffer9* ib;
	d3dContext->CreateIndexBuffer(
		m_uNumTriangles * 3 * sizeof(DWORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&ib,
		0);
	m_spIndexBuffer.reset(ib, [](IDirect3DIndexBuffer9* ib) {ib->Release(); });
}

void Terrain::Update(unsigned int delta)
{
	Object3D::Update(delta);
	if (m_bDirty)
	{
		TexVertex* vertices;
		m_spVetexBuffer->Lock(0, 0, reinterpret_cast<void**>(&vertices), 0);
		computeVertices(vertices);
		m_spVetexBuffer->Unlock();

		DWORD *indices;
		m_spIndexBuffer->Lock(0, 0, reinterpret_cast<void**>(&indices), 0);
		computeIndices(indices, D3DPT_TRIANGLELIST);
		m_spIndexBuffer->Unlock();
		m_bDirty = false;
	}
}

void Terrain::Render()
{
	d3dContext->SetTransform(D3DTS_WORLD, &m_xWorld);
	d3dContext->SetFVF(TexVertex::FVF_TEX);
	d3dContext->SetStreamSource(0, m_spVetexBuffer.get(), 0, sizeof(TexVertex));
	d3dContext->SetIndices(m_spIndexBuffer.get());
	d3dContext->SetTexture(0, m_spTexture.get());
	//d3dContext->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	d3dContext->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_uNumVertices, 0, m_uNumTriangles);

	d3dContext->SetTexture(0,0);
}

Terrain::Terrain(UINT Width, UINT Depth, UINT Height, UINT hmWidth, UINT hmHeight) :m_uWidth(Width), m_uDepth(Depth), m_uHeight(Height), m_uHeightMapWidth(hmWidth), m_uHeightMapHeight(hmHeight)
{
	m_uNumVertices = (m_uHeightMapWidth + 1)*(m_uHeightMapHeight + 1);
	m_uNumTriangles = m_uHeightMapWidth*m_uHeightMapHeight * 2;
}
