#include "Object3D.h"

using namespace Toy3D;

Object3D::Object3D()
{

}

Object3D::Object3D(Object3D&&)
{

}

Object3D::~Object3D()
{
	//to be ensure
	//delete m_pVertices;
	//delete m_pIndices;
}

void Toy3D::Object3D::SetPosition(float x, float y, float z)
{
	m_vPos = { x, y, z };
	m_bDirty = true;
}

void Toy3D::Object3D::Rotate(float x, float y, float z)
{
	m_vRotation.x += x;
	m_vRotation.y += y;
	m_vRotation.z += z;
	
	m_bDirty = true;
}

void Toy3D::Object3D::Update(unsigned int delta)
{
	if (m_bDirty)
	{
		D3DXMATRIX Rx, Ry, Rz, T;
		D3DXMatrixRotationX(&Rx, m_vRotation.x);
		D3DXMatrixRotationY(&Ry, m_vRotation.y);
		D3DXMatrixRotationZ(&Rz, m_vRotation.z);

		D3DXMatrixTranslation(
			&T,
			m_vPos.x,
			m_vPos.y,
			m_vPos.z);

		m_xWorld = Rx * Ry * Rz * T ;
		m_bDirty = false;
	}
}

std::shared_ptr<D3DContext> Toy3D::d3dContext{ nullptr };

