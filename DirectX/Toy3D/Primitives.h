#ifndef _PRIMITIVES_H_
#define _PRIMITIVES_H_

#include <d3dx9.h>
#include "Object3D.h"

namespace Toy3D
{
	namespace Primitives
	{
		class Line : public Object3D
		{
		public:
			Line();
			Line(D3DXVECTOR3 p1, D3DXVECTOR3 p2,D3DCOLOR color);
			Line(const Line& rhs);
			Line& operator=(const Line& rhs);
			Line(Line&& rhs);
			Line& operator=(Line&& rhs);
			virtual ~Line();
			
			virtual void Update(unsigned int delta) override;
			virtual void Render() override;
		protected:
			virtual void AlllocateBuffers() override;
			D3DXVECTOR3 m_vP1{ 0.0f, 0.0f, 0.0f };
			D3DXVECTOR3 m_vP2{ 0.0f, 0.0f, 0.0f };
			D3DCOLOR m_dwColor{ 0 };
		private:
			bool m_bDirty;
		};

		class Triangle : public Object3D
		{
		public:
			Triangle();
			Triangle(D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 p3, D3DCOLOR color);
			Triangle(const Triangle& rhs) = default;
			Triangle& operator=(const Triangle& rhs);
			Triangle(Triangle&& rhs);
			Triangle& operator=(Triangle&&);
			virtual ~Triangle();

			virtual void Update(unsigned int delta) override;
			virtual void Render() override;
		protected:
			virtual void AlllocateBuffers() override;
			D3DXVECTOR3 m_vP1{ 0.0f, 0.0f, 0.0f };
			D3DXVECTOR3 m_vP2{ 0.0f, 0.0f, 0.0f };
			D3DXVECTOR3 m_vP3{ 0.0f, 0.0f, 0.0f };
			D3DCOLOR m_dwColor{ 0 };
		private:
			bool m_bDirty;
		};
	}
}
#endif