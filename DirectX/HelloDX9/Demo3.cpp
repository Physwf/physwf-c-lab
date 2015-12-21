#include "Demo.h"

IDirect3DDevice9* Device = 0;

struct Vertex
{
	Vertex(float x, float y, float z, float nx, float ny, float nz) :_x(x), _y(y), _z(z), _nx(nx), _ny(ny), _nz(nz) {}
	float _x, _y, _z;
	float _nx, _ny, _nz;
	static const DWORD FVF;
};

const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL;

const int Width = 800;
const int Height = 600;

IDirect3DVertexBuffer9* Pyramid = 0;
IDirect3DIndexBuffer9* PyramidIndex = 0;

bool Setup()
{
	Device->SetRenderState(D3DRS_LIGHTING, true);

	Device->CreateVertexBuffer(
		12 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&Pyramid,
		0);

	Vertex* v;
	Pyramid->Lock(0, 0, reinterpret_cast<void**>(&v), 0);

	v[0] = Vertex(-1.0f, 0.0f, -1.0f, 0.0f, 0.707f, -0.707f);
	v[1] = Vertex(0.0f, 1.0f, 0.0f, 0.0f, 0.707f, -0.707f);
	v[2] = Vertex(1.0f, 0.0f, -1.0f, 0.0f, 0.707f, -0.707f);

	v[3] = Vertex(-1.0f, 0.0f, 1.0f, -0.707f, 0.707f, 0.0f);
	v[4] = Vertex(0.0f, 1.0f, 0.0f, -0.707f, 0.707f, 0.0f);
	v[5] = Vertex(-1.0f, 0.0f, -1.0f, -0.707f, 0.707f, 0.0f);

	v[6] = Vertex(1.0f, 0.0f, -1.0f, 0.707f, 0.707f, 0.0f);
	v[7] = Vertex(0.0f, 1.0f, 0.0f, 0.707f, 0.707f, 0.0f);
	v[8] = Vertex(1.0f, 0.0f, 1.0f, 0.707f, 0.707f, 0.0f);

	v[9] = Vertex(1.0f, 0.0f, 1.0f, 0.0f, 0.707f, 0.707f);
	v[10] = Vertex(0.0f, 1.0f, 0.0f, 0.0f, 0.707f, 0.707f);
	v[11] = Vertex(-1.0f, 0.0f, 1.0f, 0.0f, 0.707f, 0.707f);

	Pyramid->Unlock();

	D3DMATERIAL9 mtrl;
	mtrl.Ambient = d3d::WHITE;
	mtrl.Diffuse = d3d::WHITE;
	mtrl.Specular = d3d::WHITE;
	mtrl.Emissive = d3d::BLACK;
	mtrl.Power = 5.0f;

	Device->SetMaterial(&mtrl);

	D3DLIGHT9 dir;
	::ZeroMemory(&dir, sizeof(dir));
	dir.Type = D3DLIGHT_DIRECTIONAL;
	dir.Diffuse = d3d::WHITE;
	dir.Specular = d3d::WHITE * 0.3f;
	dir.Ambient = d3d::WHITE * 0.6f;
	dir.Direction = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	Device->SetLight(0, &dir);
	Device->LightEnable(0, true);

	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, true);

	D3DXVECTOR3 position(0.0f,3.0f,-5.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXMATRIX V;
	D3DXMatrixLookAtLH(&V, &position, &target, &up);
	Device->SetTransform(D3DTS_VIEW, &V);

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI*0.5f,
		static_cast<float>(Width) / Height,
		1.0,
		1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	return true;

}

bool Display(float timeDelta)
{
	if (Device)
	{
		static float y = 0;
		D3DXMATRIX WORLD;
		D3DXMatrixRotationY(&WORLD, y);

		y += 0.0001f;
		

		Device->SetTransform(D3DTS_WORLD, &WORLD);

		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);

		Device->BeginScene();
		Device->SetFVF(Vertex::FVF);
		Device->SetStreamSource(0, Pyramid, 0, sizeof(Vertex));

		//D3DXMatrixTranslation(&)

		Device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 4);

		Device->EndScene();
		Device->Present(0, 0, 0, 0);
	}
	return true;
}

void Cleanup()
{
	d3d::Release<IDirect3DVertexBuffer9*>(Pyramid);
}