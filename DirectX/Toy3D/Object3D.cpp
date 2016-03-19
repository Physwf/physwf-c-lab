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

std::shared_ptr<D3DContext> Toy3D::d3dContext{ nullptr };

