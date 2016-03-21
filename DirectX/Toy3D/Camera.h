#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Object3D.h"
#include <d3dx9.h>

namespace Toy3D
{
	class SkyBox;
	class Camera : public Object3D
	{
		friend class SkyBox;
	public:
		Camera(int sw, int sh);
		Camera(const Camera& rhs);
		Camera& operator=(const Camera& rhs);
		Camera(Camera&&);
		Camera& operator=(Camera&&);
		~Camera();

		void LookAt(const D3DXVECTOR3* pAt);
		void SetViewport(DWORD X, DWORD Y, DWORD Width, DWORD Height, float MinZ, float MaxZ);

		const D3DXMATRIX& xView() const { return m_xView; }
		const D3DXMATRIX& xProjection() const { return m_xProj; }
		const D3DVIEWPORT9 Viewport() const { return m_Viewport; }

		virtual void Rotate(float x, float y, float z) override;

		virtual void Update(unsigned int delta) override;
		virtual void Render() override;

		void Walk(float units);
		void Strafe(float units);
		void Fly(float units);

		void Yaw(float rad);
		void Pitch(float rad);
		void Roll(float rad);

	protected:
		virtual void AlllocateBuffers() override {}
	protected:
		D3DXMATRIX m_xView;
		D3DXMATRIX m_xProj;
		D3DVIEWPORT9 m_Viewport;
	private:
		int m_iScreenWidth, m_iScreenHeight;
		FLOAT m_zFar, m_zNear;
		FLOAT m_fovY;
		D3DXVECTOR3 m_vRight;//x
		D3DXVECTOR3 m_vUp;//y
		D3DXVECTOR3 m_vLook;//z
		bool m_bDirty;
	};
}
#endif