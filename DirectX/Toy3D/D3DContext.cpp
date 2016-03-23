#include "D3DContext.h"
#include <functional>

using namespace Toy3D;

D3DContext::D3DContext()
{

}

D3DContext::~D3DContext()
{

}

HRESULT D3DContext::Initialize(HWND hwnd, int width, int height, bool windowed)
{
	IDirect3D9 *d3d = Direct3DCreate9(D3D_SDK_VERSION);
	//std::function<void (D3DContext&, IDirect3D9*)> release = &D3DContext::Release<IDirect3D9*>;
	m_spD3D.reset(d3d, [](IDirect3D9* d3d) { d3d->Release(); });
	
	D3DCAPS9 caps;
	m_spD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	int vp = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
	caps.MaxVertexIndex;
	caps.MaxPrimitiveCount;
	D3DPRESENT_PARAMETERS d3dpp;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hwnd;
	d3dpp.Windowed = windowed;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat =  D3DFMT_D24S8;
	d3dpp.Flags = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	IDirect3DDevice9 *device;
	HRESULT hr = m_spD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		vp,
		&d3dpp,
		&device);
	m_spDivice.reset(device, [](IDirect3DDevice9 *device){ device->Release(); });
	return hr;
}

void D3DContext::Clear()
{
	m_spDivice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
}

void D3DContext::SetTransform(D3DTRANSFORMSTATETYPE type, const D3DMATRIX* matrix)
{
	m_spDivice->SetTransform(type, matrix);
}

void Toy3D::D3DContext::BeginScene()
{
	m_spDivice->BeginScene();
}

void Toy3D::D3DContext::EndScene()
{
	m_spDivice->EndScene();
}

void Toy3D::D3DContext::Present()
{
	m_spDivice->Present(0, 0, 0, 0);
}

void Toy3D::D3DContext::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle)
{
	HRESULT hr = m_spDivice->CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
	hr = 0;
}

void Toy3D::D3DContext::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle)
{
	m_spDivice->CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
}

void Toy3D::D3DContext::DrawIndexedPrimitive(D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinIndex, UINT NumVertices, UINT StartIndex, UINT PrimitiveCount)
{
	m_spDivice->DrawIndexedPrimitive(Type, BaseVertexIndex, MinIndex, NumVertices, StartIndex, PrimitiveCount);
}

void Toy3D::D3DContext::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	m_spDivice->DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

void Toy3D::D3DContext::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	m_spDivice->SetRenderState(State, Value);
}

void D3DContext::SetTexture(DWORD sampler, IDirect3DBaseTexture9* tex)
{
	m_spDivice->SetTexture(sampler, tex);
}

void Toy3D::D3DContext::SetIndices(IDirect3DIndexBuffer9* indexBuffer)
{
	m_spDivice->SetIndices(indexBuffer);
}

void Toy3D::D3DContext::SetFVF(DWORD FVF)
{
	m_spDivice->SetFVF(FVF);
}

void Toy3D::D3DContext::SetViewport(const D3DVIEWPORT9* vp)
{
	m_spDivice->SetViewport(vp);
}

void D3DContext::SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride)
{
	m_spDivice->SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
}
