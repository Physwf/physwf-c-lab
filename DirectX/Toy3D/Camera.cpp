#include "Camera.h"
#include "Debuger.h"

using namespace Toy3D;

Camera::Camera(int sw, int sh) :m_iScreenWidth(sw), m_iScreenHeight(sh), m_zFar(1000.0f), m_zNear(1.0f), m_fovY(D3DX_PI*0.3)
{
	m_Viewport = { 0, 0, sw, sh, 0, 1 };
	m_vUp = { 0.0f, 1.0f, 0.0f };
	m_vRight = { 1.0f, 0.0f, 0.0f };
	m_vLook = { 0.0f, 0.0f, 1.0f };
	D3DXMatrixIdentity(&m_xWorld);
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

void Camera::LookAt(const D3DXVECTOR3* pAt)
{
	m_vLook = *pAt - m_vPos;
	m_bDirty = true;
}

void Camera::SetViewport(DWORD x, DWORD y, DWORD width, DWORD height, float MinZ, float MaxZ)
{
	m_Viewport = { x, y, width, height, MinZ, MaxZ };
}

void Camera::Update(unsigned int delta)
{
	Object3D::Update(delta);
	if (m_bDirty)
	{
		D3DXMatrixPerspectiveFovLH(
			&m_xProj,
			m_fovY,
			static_cast<float>(m_iScreenWidth) / m_iScreenHeight,
			m_zNear,
			m_zFar);

		D3DXVec3Normalize(&m_vLook, &m_vLook);

		D3DXVec3Cross(&m_vUp, &m_vLook, &m_vRight);
		D3DXVec3Normalize(&m_vUp, &m_vUp);

		D3DXVec3Cross(&m_vRight, &m_vUp, &m_vLook);
		D3DXVec3Normalize(&m_vRight, &m_vRight);

		float x = -D3DXVec3Dot(&m_vRight, &m_vPos);
		float y = -D3DXVec3Dot(&m_vUp, &m_vPos);
		float z = -D3DXVec3Dot(&m_vLook, &m_vPos);

		m_xView(0, 0) = m_vRight.x;
		m_xView(0, 1) = m_vUp.x;
		m_xView(0, 2) = m_vLook.x;
		m_xView(0, 3) = 0.0f;

		m_xView(1, 0) = m_vRight.y;
		m_xView(1, 1) = m_vUp.y;
		m_xView(1, 2) = m_vLook.y;
		m_xView(1, 3) = 0.0f;
		
		m_xView(2, 0) = m_vRight.z;
		m_xView(2, 1) = m_vUp.z;
		m_xView(2, 2) = m_vLook.z;
		m_xView(2, 3) = 0.0f;

		m_xView(3, 0) = x;
		m_xView(3, 1) = y;
		m_xView(3, 2) = z;
		m_xView(3, 3) = 1.0f;

		m_bDirty = false;
	}
}

void Camera::Render()
{
	d3dContext->SetTransform(D3DTS_VIEW, &m_xView);
	d3dContext->SetTransform(D3DTS_PROJECTION, &m_xProj);
	//d3dContext->SetTransform(D3DTS_WORLD, &m_xWorld);
	d3dContext->SetViewport(&m_Viewport);
}

void Camera::Rotate(float x, float y, float z)
{
	Object3D::Rotate(x, y, z);
	// to do
	m_bDirty = true;
}

void Camera::Walk(float units)
{
	m_vPos += units*m_vLook;
	m_bDirty = true;
}

void Camera::Strafe(float units)
{
	m_vPos += units*m_vRight;
	m_bDirty = true;
}

void Camera::Fly(float units)
{
	m_vPos += units*m_vUp;
	m_bDirty = true;
}

void Camera::Yaw(float rad)
{
	if (rad != 0.0f)
	{
		D3DXMATRIX rotation;
		D3DXMatrixRotationAxis(&rotation, &m_vUp, rad);
		D3DXVec3TransformNormal(&m_vRight, &m_vRight, &rotation);
		D3DXVec3TransformNormal(&m_vLook, &m_vLook, &rotation);
		m_bDirty = true;
	}
}

void Camera::Pitch(float rad)
{
	if (rad != 0.0f)
	{
		D3DXMATRIX rotation;
		D3DXMatrixRotationAxis(&rotation, &m_vRight, rad);
		D3DXVec3TransformNormal(&m_vUp, &m_vUp, &rotation);
		D3DXVec3TransformNormal(&m_vLook, &m_vLook, &rotation);
		m_bDirty = true;
	}
}

void Camera::Roll(float rad)
{
	if (rad != 0.0f)
	{
		D3DXMATRIX rotation;
		D3DXMatrixRotationAxis(&rotation, &m_vLook, rad);
		D3DXVec3TransformNormal(&m_vRight, &m_vRight, &rotation);
		D3DXVec3TransformNormal(&m_vUp, &m_vUp, &rotation);
		m_bDirty = true;
	}
}
