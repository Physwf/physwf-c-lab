#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <memory>
#include <list>
#include <set>
#include <d3dx9.h>
#include "Vertex.h"
#include "D3DContext.h"

namespace Toy3D
{
	class Object3D
	{
	public:
		Object3D();
		Object3D(const Object3D&) = default;
		Object3D& operator=(const Object3D&) = default;
		Object3D(Object3D&&);
		Object3D& operator=(Object3D&&);
		virtual ~Object3D();

		const D3DXVECTOR3& vPositioin() const { return m_vPos; }
		const D3DXMATRIX& xTransform() const { return m_xWorld; }

		virtual void SetPosition(float x,float y,float z);
		virtual void Rotate(float x, float y, float z);


		virtual void Update(unsigned int delta);
		virtual void Render() = 0;
	protected:
		virtual void AlllocateBuffers() = 0;
	protected:
		D3DXVECTOR3 m_vPos{ 0.0f, 0.0f, 0.0f };
		D3DXVECTOR3 m_vRotation{ 0.0f, 0.0f, 0.0f };
		D3DXMATRIX m_xWorld;
		std::shared_ptr<IDirect3DVertexBuffer9> m_spVetexBuffer{ nullptr };
		std::shared_ptr<IDirect3DIndexBuffer9> m_spIndexBuffer{ nullptr };
	private:
		bool m_bDirty;
	};
	extern std::shared_ptr<D3DContext> d3dContext;
	typedef std::shared_ptr<Object3D> SP_Object;
	typedef std::list<SP_Object> object_list_t;
	typedef std::set<SP_Object> object_set_t;
}
#endif