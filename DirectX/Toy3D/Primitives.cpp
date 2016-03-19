#include "Primitives.h"

using namespace Toy3D::Primitives;

Line::Line()
{
	AlllocateBuffers();
	m_bDirty = true;
}

Line::Line(D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DCOLOR color) :m_vP1(p1), m_vP2(p2), m_dwColor(color)
{
	AlllocateBuffers();
	m_bDirty = true;
}

Toy3D::Primitives::Line::~Line()
{

}


void Toy3D::Primitives::Line::AlllocateBuffers()
{
	IDirect3DVertexBuffer9* vb;
	d3dContext->CreateVertexBuffer(
		2 * sizeof(ColorVertex),
		D3DUSAGE_WRITEONLY,
		ColorVertex::FVF_COLOR,
		D3DPOOL_MANAGED,
		&vb,
		0);
	m_spVetexBuffer.reset(vb, [](IDirect3DVertexBuffer9* vb) { vb->Release(); });
}

void Line::Update(unsigned int delta)
{
	if (m_bDirty)
	{
		ColorVertex* cVertex;
		m_spVetexBuffer->Lock(0, 0, reinterpret_cast<void**>(&cVertex), 0);
		cVertex[0] = ColorVertex(m_vP1.x, m_vP1.y, m_vP1.z, m_dwColor);
		cVertex[1] = ColorVertex(m_vP2.x, m_vP2.y, m_vP2.z, m_dwColor);
		m_spVetexBuffer->Unlock();

		D3DXMatrixTranslation(
			&m_xWorld,
			m_vPos.x,
			m_vPos.y,
			m_vPos.z);

		m_bDirty = false;
	}
}

void Line::Render()
{
	d3dContext->SetTransform(D3DTS_WORLD, &m_xWorld);
	d3dContext->SetFVF(ColorVertex::FVF_COLOR);
	d3dContext->SetStreamSource(0, m_spVetexBuffer.get(), 0, sizeof(ColorVertex));
	d3dContext->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	d3dContext->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	d3dContext->DrawPrimitive(D3DPT_LINELIST, 0, 1);
}

Triangle::Triangle()
{
	m_bDirty = true;
	AlllocateBuffers();
}

Triangle::Triangle(D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 p3, D3DCOLOR color) :m_vP1(p1), m_vP2(p2), m_vP3(p3), m_dwColor(color)
{
	m_bDirty = true;
	AlllocateBuffers();
}

Triangle& Triangle::operator=(const Triangle& rhs)
{
	return *this;
}

Triangle::Triangle(Triangle&& rhs)
{

}

Triangle& Triangle::operator=(Triangle&&)
{
	return *this;
}

Triangle::~Triangle()
{

}

void Triangle::Update(unsigned int delta)
{
	if (m_bDirty)
	{
		ColorVertex* cVertex;
		m_spVetexBuffer->Lock(0, 0, reinterpret_cast<void**>(&cVertex), 0);
		cVertex[0] = ColorVertex(m_vP1.x, m_vP1.y, m_vP1.z, m_dwColor);
		cVertex[1] = ColorVertex(m_vP2.x, m_vP2.y, m_vP2.z, m_dwColor);
		cVertex[2] = ColorVertex(m_vP3.x, m_vP3.y, m_vP3.z, m_dwColor);
		m_spVetexBuffer->Unlock();

		D3DXMatrixTranslation(
			&m_xWorld,
			m_vPos.x,
			m_vPos.y,
			m_vPos.z);

		m_bDirty = false;
	}
}

void Triangle::Render()
{
	d3dContext->SetTransform(D3DTS_WORLD, &m_xWorld);
	d3dContext->SetFVF(ColorVertex::FVF_COLOR);
	d3dContext->SetStreamSource(0, m_spVetexBuffer.get(), 0, sizeof(ColorVertex));
	d3dContext->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	d3dContext->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_FLAT);
	d3dContext->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}

void Triangle::AlllocateBuffers()
{
	IDirect3DVertexBuffer9* vb;
	d3dContext->CreateVertexBuffer(
		3 * sizeof(ColorVertex),
		D3DUSAGE_WRITEONLY,
		ColorVertex::FVF_COLOR,
		D3DPOOL_MANAGED,
		&vb,
		0);
	m_spVetexBuffer.reset(vb, [](IDirect3DVertexBuffer9*vb) { vb->Release(); });
}
