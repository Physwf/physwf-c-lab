#ifndef _D3DCONTEXT_H_
#define _D3DCONTEXT_H_

#include <d3d9.h>
#include <windows.h>
#include <memory>

namespace Toy3D
{
	class D3DContext
	{
	public:
		D3DContext();
		D3DContext(const D3DContext&) = delete;
		D3DContext& operator=(const D3DContext& rhs) = delete;
		D3DContext(D3DContext&&) = delete;
		D3DContext& operator=(D3DContext&&) = delete;
		virtual ~D3DContext();

		HRESULT Initialize(HWND hwnd, int width, int height, bool windowed);
		
		void CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE*pSharedHandle);
		void CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE*pSharedHandle);
		
		void DrawIndexedPrimitive(D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinIndex, UINT NumVertices, UINT StartIndex,UINT PrimitiveCount);
		void DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount);
		
		void SetRenderState(D3DRENDERSTATETYPE State, DWORD Value);
		void SetTransform(D3DTRANSFORMSTATETYPE type, const D3DMATRIX* matrix);
		void SetTexture(DWORD sampler, IDirect3DBaseTexture9* tex);
		void SetIndices(IDirect3DIndexBuffer9* indexBuffer);
		void SetFVF(DWORD FVF);
		void SetViewport(const D3DVIEWPORT9* vp);
		void SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride);
		
		void Clear();
		void BeginScene();
		void EndScene();
		void Present();

		std::shared_ptr<IDirect3DDevice9> GetDevice() { return m_spDivice; }
	protected:
		template <typename T> void Release(T t)
		{
			if (t)
			{
				t->Release();
				t = nullptr;
			}
		}
		template <typename T> void Delete(T t)
		{
			if (t)
			{
				delete t;
				t = nullptr;
			}
		}
	private:
		std::shared_ptr<IDirect3D9> m_spD3D{ nullptr };
		std::shared_ptr<IDirect3DDevice9> m_spDivice{ nullptr };
	};

}
#endif