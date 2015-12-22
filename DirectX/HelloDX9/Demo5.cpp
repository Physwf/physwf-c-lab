#include "Demo.h"

IDirect3DDevice9* Device = 0;

const int Width = 800;
const int Height = 600;

struct Vertex
{
	float _x, _y, _z;
	float _nx, _ny, _nz;
	float _u, _v;

	Vertex(float x, float y, float z, float nx,float ny, float nz,float u, float v) :_x(x), _y(y), _z(z),_nx(nx),_ny(ny),_nz(nz), _u(u), _v(v){};

	static const WORD FVF;
};

const WORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
ID3DXMesh* Teapot = 0;
D3DMATERIAL9 TeapotMtrl;

IDirect3DVertexBuffer9* BkGndQuad = 0;
IDirect3DTexture9* BkGndTex = 0;
D3DMATERIAL9 BkGndMtrl;

bool Setup()
{
	TeapotMtrl = d3d::RED_MTRL;
	TeapotMtrl.Diffuse.a = 0.5f;

	BkGndMtrl = d3d::WHITE_MTRL;

	Device->CreateVertexBuffer(
		6 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&BkGndQuad,
		0);

	D3DXCreateTeapot(Device, &Teapot, 0);

	Vertex* v;
	BkGndQuad->Lock(0, 0, reinterpret_cast<void**>(&v), 0);

	v[0] = Vertex(-10.0f, -10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[1] = Vertex(-10.0f, 10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[2] = Vertex(10.0f, 10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	v[3] = Vertex(-10.0f, -10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[4] = Vertex(10.0f, 10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[5] = Vertex(10.0f, -10.0f, 5.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);

	BkGndQuad->Unlock();

	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Diffuse = d3d::WHITE;
	light.Specular = d3d::WHITE * 0.2f;
	light.Ambient = d3d::WHITE * 0.6f;
	light.Direction = D3DXVECTOR3(0.707f, 0.0f, 0.707f);

	Device->SetLight(0, &light);
	Device->LightEnable(0, true);

	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, true);

	D3DXCreateTextureFromFile(
		Device,
		L"crate.jpg",
		&BkGndTex);

	Device->SetSamplerState(0, D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	D3DXMATRIX V;
	D3DXVECTOR3 pos(0.0f, 0.0f, -3.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXMatrixLookAtLH(&V, &pos, &target, &up);

	Device->SetTransform(D3DTS_VIEW, &V);
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(&proj,
		D3DX_PI*0.5f,
		static_cast<float>(Width) / Height,
		0.0f,
		1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	return true;
}

bool Display(float timeDelta)
{
	if (Device)
	{
		if (::GetAsyncKeyState('A') & 0x8000f)
			TeapotMtrl.Diffuse.a += 0.01f;
		if (::GetAsyncKeyState('S') & 0x8000f)
			TeapotMtrl.Diffuse.a -= 0.01f;

		if (TeapotMtrl.Diffuse.a > 1.0f)
			TeapotMtrl.Diffuse.a = 1.0f;
		if (TeapotMtrl.Diffuse.a < 0.0f)
			TeapotMtrl.Diffuse.a = 0.0f;

		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);

		Device->BeginScene();

		D3DXMATRIX W;
		D3DXMatrixIdentity(&W);
		Device->SetTransform(D3DTS_WORLD, &W);
		Device->SetFVF(Vertex::FVF);
		Device->SetStreamSource(0, BkGndQuad, 0, sizeof(Vertex));
		Device->SetMaterial(&BkGndMtrl);
		Device->SetTexture(0, BkGndTex);
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

		D3DXMatrixScaling(&W, 1.5f, 1.5f, 1.5f);
		Device->SetTransform(D3DTS_WORLD, &W);
		Device->SetMaterial(&TeapotMtrl);
		Device->SetTexture(0, 0);
		Teapot->DrawSubset(0);

		Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

		Device->EndScene();

		Device->Present(0, 0, 0, 0);
	}
	return true;
}

void Cleanup()
{
	d3d::Release<IDirect3DVertexBuffer9*>(BkGndQuad);
	d3d::Release<IDirect3DTexture9*>(BkGndTex);
	Teapot->Release();
}