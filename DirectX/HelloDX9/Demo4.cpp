#include "Demo.h"

IDirect3DDevice9 *Device = 0;

const int Width = 800;
const int Height = 600;

struct Vertex
{
	float _x, _y, _z;
	float _nx, _ny, _nz;
	float _u, _v;

	Vertex(float x, float y, float z, float nx,float ny, float nz, float u, float v) :_x(x), _y(y), _z(z),_nx(nx),_ny(ny),_nz(nz), _u(u), _v(v) {}

	static const WORD FVF;
};

const WORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

IDirect3DVertexBuffer9* Quad;
IDirect3DIndexBuffer9* QuadIndex;
IDirect3DTexture9* Tex;

bool Setup()
{
	Device->CreateVertexBuffer(
		6 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&Quad,
		0);

	Vertex* v;

	Quad->Lock(0, 0, reinterpret_cast<void**>(&v), 0);

	v[0] = Vertex(-1.0f, -1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 0.0f, 3.0f);
	v[1] = Vertex(-1.0f, 1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[2] = Vertex(1.0f, 1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 3.0f, 0.0f);

	v[3] = Vertex(-1.0f, -1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 0.0f, 3.0f);
	v[4] = Vertex(1.0f, 1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 3.0f, 0.0f);
	v[5] = Vertex(1.0f, -1.0f, 1.25f, 0.0f, 0.0f, -1.0f, 3.0f, 3.0f);

	Quad->Unlock();

	/*Device->CreateIndexBuffer(6 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&QuadIndex,
		0);*/

	D3DXCreateTextureFromFile(
		Device,
		L"dx5_logo.bmp",
		&Tex);

	Device->SetTexture(0, Tex);

	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	Device->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI*0.5f,
		static_cast<float>(Width) / Height,
		1.0f,
		1000.0f);

	Device->SetTransform(D3DTS_PROJECTION, &proj);

	return true;
}

bool Display(float timeDelta)
{
	if (Device)
	{
		Device->Clear(0, 0, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,0xffffffff, 1.0f, 0);

		Device->BeginScene();
		Device->SetStreamSource(0, Quad, 0, sizeof(Vertex));
		Device->SetFVF(Vertex::FVF);
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
		Device->EndScene();
		Device->Present(0, 0, 0, 0);
	}
	return true;
}

void Cleanup()
{
	d3d::Release<IDirect3DVertexBuffer9*>(Quad);
	d3d::Release<IDirect3DTexture9*>(Tex);
}