#include "Camera.h"

using namespace Toy3D;

Camera::Camera(int sw, int sh) :m_iScreenWidth(sw), m_iScreenHeight(sh), m_zFar(1000.0f), m_zNear(1.0f), m_fovY(D3DX_PI*0.5)
{
	m_Viewport = { 0, 0, sw, sh, 0, 1 };
	m_bDirty = true;
}

Camera::Camera(const Camera& rhs)
{

}

Camera::Camera(Camera&&)
{

}


Camera::~Camera()
{

}

void Camera::LookAt(const D3DXVECTOR3* pAt, const D3DXVECTOR3* pUp)
{
	D3DXMatrixLookAtLH(&m_xView, &m_vPos, pAt, pUp);
	m_bDirty = true;
}

void Camera::SetViewport(DWORD x, DWORD y, DWORD width, DWORD height, float MinZ, float MaxZ)
{
	m_Viewport = { x, y, width, height, MinZ, MaxZ };
	m_bDirty = true;
}

void Camera::Update(unsigned int delta)
{
	if (m_bDirty)
	{
		D3DXMatrixPerspectiveFovLH(
			&m_xProj,
			m_fovY,
			static_cast<float>(m_iScreenWidth) / m_iScreenHeight,
			m_zNear,
			m_zFar);

		d3dContext->SetTransform(D3DTS_VIEW, &m_xView);
		d3dContext->SetTransform(D3DTS_PROJECTION, &m_xProj);
		d3dContext->SetViewport(&m_Viewport);
		m_bDirty = false;
	}
}

void Camera::Render()
{
	
}
