#include "SkyBox.h"

using namespace Toy3D;

SkyBox::~SkyBox()
{

}

std::shared_ptr<SkyBox> SkyBox::Create(std::shared_ptr<Camera> c,const char* file)
{
	auto device = d3dContext->GetDevice();
	IDirect3DCubeTexture9* cube{nullptr};
	//HRESULT hr = D3DXCreateCubeTextureFromFileEx(
	//	device.get(),
	//	file,
	//	D3DX_DEFAULT,
	//	D3DX_DEFAULT,
	//	0,
	//	D3DFMT_UNKNOWN,
	//	D3DPOOL_MANAGED,
	//	D3DX_DEFAULT,
	//	D3DX_DEFAULT,
	//	0,
	//	NULL,
	//	NULL,
	//	&cube);
	HRESULT hr = D3DXCreateCubeTextureFromFile(device.get(), file, &cube);
	if (hr == D3DXERR_INVALIDDATA)
		if (D3D_OK != hr) return std::shared_ptr<SkyBox>(nullptr);
	auto sb = std::make_shared<SkyBox>(c);
	sb->m_spCubeTexture.reset(cube, [](IDirect3DCubeTexture9* ct){ ct->Release(); });
	sb->AlllocateBuffers();
	sb->m_bDirty = true;
	return sb;
}

void SkyBox::Update(unsigned int delta)
{
	if (m_bDirty)
	{
		D3DSURFACE_DESC sd;
		m_spCubeTexture->GetLevelDesc(0, &sd);
		float half_size = static_cast<float>(sd.Width)/2;

		SkyBoxVertex* sVertices;
		m_spVetexBuffer->Lock(0, 0, reinterpret_cast<void**>(&sVertices), 0);
		//bottom
		sVertices[0] = SkyBoxVertex(-half_size, -half_size, -half_size, 1, -1.0f, -1);//0
		sVertices[1] = SkyBoxVertex(-half_size, -half_size, half_size, 1, -1.0f, 1);//3
		sVertices[2] = SkyBoxVertex(half_size, -half_size, -half_size, -1, -1.0f, -1);//1

		sVertices[3] = SkyBoxVertex(half_size, -half_size, -half_size, -1, -1.0f, -1);//1
		sVertices[4] = SkyBoxVertex(-half_size, -half_size, half_size, 1, -1.0f, 1);//3
		sVertices[5] = SkyBoxVertex(half_size, -half_size, half_size, -1, -1.0f, 1);//2
		//right
		sVertices[6] = SkyBoxVertex(half_size, -half_size, -half_size, 1.0f, -1, -1);//1
		sVertices[7] = SkyBoxVertex(half_size, -half_size, half_size, 1.0f, -1, 1);//2
		sVertices[8] = SkyBoxVertex(half_size, half_size, -half_size, 1.0f, 1, -1);//5

		sVertices[9] = SkyBoxVertex(half_size, -half_size, half_size, 1.0f, -1, 1);//2
		sVertices[10] = SkyBoxVertex(half_size, half_size, half_size, 1.0f, 1, 1);//6
		sVertices[11] = SkyBoxVertex(half_size, half_size, -half_size, 1.0f, 1, -1);//5
		//back
		sVertices[12] = SkyBoxVertex(-half_size, -half_size, half_size, -1, -1, 1.0f);//3
		sVertices[13] = SkyBoxVertex(-half_size, half_size, half_size, -1, 1, 1.0f);//7
		sVertices[14] = SkyBoxVertex(half_size, -half_size, half_size, 1, -1, 1.0f);//2

		sVertices[15] = SkyBoxVertex(-half_size, half_size, half_size, -1, 1, 1.0f);//7
		sVertices[16] = SkyBoxVertex(half_size, half_size, half_size, 1, 1, 1.0f);//6
		sVertices[17] = SkyBoxVertex(half_size, -half_size, half_size, 1, -1, 1.0f);//2
		//left
		sVertices[18] = SkyBoxVertex(-half_size, -half_size, -half_size, -1.0f, -1, -1);//0
		sVertices[19] = SkyBoxVertex(-half_size, half_size, -half_size, -1.0f, 1, -1);//4
		sVertices[20] = SkyBoxVertex(-half_size, -half_size, half_size, -1.0f, -1, 1);//3

		sVertices[21] = SkyBoxVertex(-half_size, -half_size, half_size, -1.0f, -1, 1);//3
		sVertices[22] = SkyBoxVertex(-half_size, half_size, -half_size, -1.0f, 1, -1);//4
		sVertices[23] = SkyBoxVertex(-half_size, half_size, half_size, -1.0f, 1, 1);//7
		//front
		sVertices[24] = SkyBoxVertex(half_size, -half_size, -half_size, 1, -1, -1.0f);//1
		sVertices[25] = SkyBoxVertex(-half_size, half_size, -half_size, -1, 1, -1.0f);//4
		sVertices[26] = SkyBoxVertex(-half_size, -half_size, -half_size, -1, -1, -1.0f);//0

		sVertices[27] = SkyBoxVertex(half_size, -half_size, -half_size, 1, -1, -1.0f);//1
		sVertices[28] = SkyBoxVertex(half_size, half_size, -half_size, 1, 1, -1.0f);//5
		sVertices[29] = SkyBoxVertex(-half_size, half_size, -half_size, -1, 1, -1.0f);//4
		//top
		sVertices[30] = SkyBoxVertex(-half_size, half_size, -half_size, -1, 1.0, -1);//4
		sVertices[31] = SkyBoxVertex(half_size, half_size, -half_size, 1, 1.0, -1);//5
		sVertices[32] = SkyBoxVertex(-half_size, half_size, half_size, -1, 1.0, 1);//7

		sVertices[33] = SkyBoxVertex(half_size, half_size, half_size, 1, 1.0f, 1);//6
		sVertices[34] = SkyBoxVertex(-half_size, half_size, half_size, -1, 1.0f, 1);//7
		sVertices[35] = SkyBoxVertex(half_size, half_size, -half_size, 1, 1.0f, -1);//5
		/*
		sVertices[0] = SkyBoxVertex(-half_size, -half_size, -half_size, 0.5, 0.5, 2);//0
		sVertices[1] = SkyBoxVertex(half_size, -half_size, -half_size, 0.5, 0.5, 2);//1
		sVertices[2] = SkyBoxVertex(half_size, -half_size, half_size, 0.5, 0.5, 2);//2
		sVertices[3] = SkyBoxVertex(-half_size, -half_size, half_size, 0.5, 0.5, 2);//3
		sVertices[4] = SkyBoxVertex(-half_size, half_size, -half_size, 0.5, 0.5, 2);//4
		sVertices[5] = SkyBoxVertex(half_size, half_size, -half_size, 0.5, 0.5, 2);//5
		sVertices[6] = SkyBoxVertex(half_size, half_size, half_size, 0.5, 0.5, 2);//6
		sVertices[7] = SkyBoxVertex(-half_size, half_size, half_size, 0.5, 0.5, 2);//7
		*/
		m_spVetexBuffer->Unlock();
		/*
		WORD* indices;
		m_spIndexBuffer->Lock(0, 0, reinterpret_cast<void**>(&indices), 0);
		WORD temp[36] = {
			0, 3, 1,
			1, 3, 2,
			1, 2, 5,
			2, 6, 5,
			3, 7, 2,
			7, 6, 2,
			0, 4, 3,
			3, 4, 7,
			1, 4, 0,
			1, 5, 4,
			4, 5, 7,
			6, 7, 5,
		};
		memcpy(indices, temp, sizeof(temp));
		m_spIndexBuffer->Unlock();
		*/
		
		/*D3DXMATRIX m;
		D3DXMatrixIdentity(&m);
		d3dContext->SetTransform(D3DTS_PROJECTION, &m);*/
		m_bDirty = false;
	}
}

void SkyBox::Render()
{
	D3DXMatrixTranslation(&m_xWorld, m_spCamera->m_vPos.x, m_spCamera->m_vPos.y, m_spCamera->m_vPos.z);
	d3dContext->SetTransform(D3DTS_WORLD, &m_xWorld);
	d3dContext->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	d3dContext->SetFVF(SkyBoxVertex::FVF_SKYBOX);
	d3dContext->SetTexture(0, m_spCubeTexture.get());
	d3dContext->SetStreamSource(0, m_spVetexBuffer.get(), 0, sizeof(SkyBoxVertex));
	//d3dContext->SetIndices(m_spIndexBuffer.get());
	//d3dContext->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
	d3dContext->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 12);

	d3dContext->SetTexture(0, 0);
}

void SkyBox::AlllocateBuffers()
{
	IDirect3DVertexBuffer9* vb;
	d3dContext->CreateVertexBuffer(
		36 * sizeof(SkyBoxVertex),
		D3DUSAGE_WRITEONLY,
		TexVertex::FVF_TEX,
		D3DPOOL_MANAGED,
		&vb,
		0);
	m_spVetexBuffer.reset(vb, [](IDirect3DVertexBuffer9* vb){ vb->Release(); });
	/*
	IDirect3DIndexBuffer9* ib;
	d3dContext->CreateIndexBuffer(
		36 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&ib,
		0);
	m_spIndexBuffer.reset(ib, [](IDirect3DIndexBuffer9* ib){ ib->Release(); });
	*/
}
