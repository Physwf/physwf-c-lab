#include "Demo.h"

IDirect3DDevice9* Device = 0;

const int width = 800;
const int height = 600;

struct Vertex
{
	float _x, _y, _z;
	float _nx, _ny, _nz;
	float _u, _v;
	Vertex(float x, float y, float z, float nx, float ny, float nz,float u, float v):_x(x),_y(y),_z(z),_nx(nx),_ny(ny),_nz(nz),_u(u),_v(v) {}

	static const DWORD FVF;
};

const DWORD Vertex::FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;

ID3DXMesh* Teapot = 0;
D3DMATERIAL9 TeapotMtrl;
D3DXVECTOR3 TeapotPosition(0.0f, 5.0f, -7.0f);

IDirect3DVertexBuffer9* MirrorVB;
D3DMATERIAL9 MirrorMtrl;
IDirect3DTexture9* MirrorTex;

IDirect3DVertexBuffer9* WallVB;
D3DMATERIAL9 WallMtrl;
IDirect3DTexture9* WallTex;

IDirect3DVertexBuffer9* FloorVB;
D3DMATERIAL9 FloorMtrl;
IDirect3DTexture9* FloorTex;


void RenderMirror();
void RenderShadow();

bool Setup()
{
	D3DXCreateTeapot(Device, &Teapot, 0);
	::ZeroMemory(&TeapotMtrl, sizeof(D3DMATERIAL9));
	TeapotMtrl = d3d::RED_MTRL;

	Device->CreateVertexBuffer(
		6 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&MirrorVB,
		0);

	Device->CreateVertexBuffer(
		6 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&WallVB,
		0);

	Device->CreateVertexBuffer(
		6 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&FloorVB,
		0);

	Vertex* v;
	MirrorVB->Lock(0, 0, reinterpret_cast<void**>(&v), 0);

	v[0] = Vertex(-5.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	v[1] = Vertex(-5.0f, 10.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	v[2] = Vertex(5.0f, 10.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	v[3] = Vertex(5.0f, 10.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	v[4] = Vertex(5.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
	v[5] = Vertex(-5.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);

	MirrorVB->Unlock();

	Vertex* vWall;
	WallVB->Lock(0, 0, reinterpret_cast<void**>(&vWall), 0);

	vWall[0] = Vertex(-5.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	vWall[1] = Vertex(-5.0f, 10.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	vWall[2] = Vertex(5.0f, 10.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	vWall[3] = Vertex(5.0f, 10.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f);
	vWall[4] = Vertex(5.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
	vWall[5] = Vertex(-5.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f);

	WallVB->Unlock();

	Vertex* vFloor;
	FloorVB->Lock(0, 0, reinterpret_cast<void**>(&vFloor), 0);

	vFloor[0] = Vertex(-15.0f, 0.0f, -15.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	vFloor[1] = Vertex(-15.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	vFloor[2] = Vertex(15.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

	vFloor[3] = Vertex(15.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f);
	vFloor[4] = Vertex(15.0f, 0.0f, -15.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
	vFloor[5] = Vertex(-15.0f, 0.0f, -15.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);

	FloorVB->Unlock();

	MirrorMtrl = d3d::WHITE_MTRL;
	WallMtrl = d3d::WHITE_MTRL;
	FloorMtrl = d3d::WHITE_MTRL;

	D3DXCreateTextureFromFile(Device, L"ice.bmp", &MirrorTex);
	D3DXCreateTextureFromFile(Device, L"brick0.jpg", &WallTex);
	D3DXCreateTextureFromFile(Device, L"checker.jpg", &FloorTex);

	Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	D3DLIGHT9 dir;
	::ZeroMemory(&dir, sizeof(dir));
	dir.Type = D3DLIGHT_DIRECTIONAL;
	dir.Diffuse = d3d::WHITE;
	dir.Specular = d3d::WHITE * 0.2f;
	dir.Ambient = d3d::WHITE * 0.6f;
	dir.Direction = D3DXVECTOR3(0.707f, -0.707f, 0.707f);

	Device->SetLight(0, &dir);
	Device->LightEnable(0, true);
	Device->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	Device->SetRenderState(D3DRS_SPECULARENABLE, true);

	D3DXMATRIX V;
	//D3DXVECTOR3 pos(-10.0f, 10.0f, -10.0f);
	D3DXVECTOR3 pos(0.0f, 10.0f, -15.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&V, &pos, &target, &up);
	Device->SetTransform(D3DTS_VIEW, &V);

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(
		&proj,
		D3DX_PI*0.5,
		static_cast<float>(width) / height,
		1.0f,
		1000.0f);
	Device->SetTransform(D3DTS_PROJECTION, &proj);

	return true;
}

bool Display(float timeDelta)
{
	Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 0, 1.0f, 0);

	Device->BeginScene();
	
	//draw wall
	Device->SetTexture(0, WallTex);
	Device->SetStreamSource(0, WallVB, 0, sizeof(Vertex));
	Device->SetFVF(Vertex::FVF);
	Device->SetMaterial(&WallMtrl);

	D3DXMATRIX W;
	D3DXMatrixIdentity(&W);
	D3DXMatrixTranslation(&W, -10.0f, 0.0f, 0.0f);
	Device->SetTransform(D3DTS_WORLD, &W);
	Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	D3DXMatrixIdentity(&W);
	D3DXMatrixTranslation(&W, 10.0f, 0.0f, 0.0f);
	Device->SetTransform(D3DTS_WORLD, &W);
	Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
	//draw mirror
	Device->SetTexture(0, MirrorTex);
	Device->SetStreamSource(0, MirrorVB, 0, sizeof(Vertex));
	D3DXMatrixIdentity(&W);
	Device->SetTransform(D3DTS_WORLD, &W);
	Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
	//draw floor
	Device->SetTexture(0, FloorTex);
	Device->SetStreamSource(0, FloorVB, 0, sizeof(Vertex));
	Device->SetFVF(Vertex::FVF);
	Device->SetMaterial(&FloorMtrl);

	D3DXMatrixIdentity(&W);
	Device->SetTransform(D3DTS_WORLD, &W);
	Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	//draw teapot
	D3DXMatrixIdentity(&W);
	D3DXMatrixTranslation(&W, TeapotPosition.x, TeapotPosition.y, TeapotPosition.z);
	Device->SetTransform(D3DTS_WORLD, &W);
	Device->SetMaterial(&TeapotMtrl);
	Teapot->DrawSubset(0);

	RenderMirror();
	RenderShadow();

	Device->EndScene();
	Device->Present(0, 0, 0, 0);

	return true;
}

void RenderMirror()
{
	Device->SetRenderState(D3DRS_STENCILENABLE, true);
	Device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);
	Device->SetRenderState(D3DRS_STENCILREF, 0x1);
	Device->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
	Device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
	Device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	Device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	Device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);
	// disable write to the depth and back buffer
	Device->SetRenderState(D3DRS_ZWRITEENABLE, false);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//draw the mirror to the stencil buffer
	Device->SetStreamSource(0, MirrorVB, 0, sizeof(Vertex));
	Device->SetFVF(Vertex::FVF);
	Device->SetMaterial(&MirrorMtrl);
	Device->SetTexture(0, MirrorTex);
	D3DXMATRIX I;
	D3DXMatrixIdentity(&I);
	Device->SetTransform(D3DTS_WORLD, &I);
	Device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	//re-enable depth writes
	Device->SetRenderState(D3DRS_ZWRITEENABLE, true);
	Device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	Device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

	
	D3DXMATRIX W, T, R;
	D3DXPLANE plane(0.0f, 0.0f, 1.0f, 0.0f);
	D3DXMatrixReflect(&R, &plane);
	D3DXMatrixTranslation(&T,
		TeapotPosition.x,
		TeapotPosition.y,
		TeapotPosition.z);

	W = T*R;

	Device->Clear(0, 0, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

	Device->SetTransform(D3DTS_WORLD, &W);
	Device->SetMaterial(&TeapotMtrl);
	Device->SetTexture(0, 0);
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	Teapot->DrawSubset(0);

	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	Device->SetRenderState(D3DRS_STENCILENABLE, false);
	Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

void RenderShadow()
{
	Device->SetRenderState(D3DRS_STENCILENABLE, true);
	Device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
	Device->SetRenderState(D3DRS_STENCILREF, 0x0);
	Device->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
	Device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);
	Device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	Device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	Device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);

	D3DXVECTOR4 lightDirection(0.707f, -0.707f, 0.707f, 0.0f);
	D3DXPLANE groundPlane(0.0f, -1.0f, 0.0f, 0.0f);
	D3DXMATRIX S;
	D3DXMatrixShadow(&S,
		&lightDirection,
		&groundPlane);
	D3DXMATRIX T;
	D3DXMatrixTranslation(
		&T,
		TeapotPosition.x,
		TeapotPosition.y,
		TeapotPosition.z);

	D3DXMATRIX W = T * S;
	Device->SetTransform(D3DTS_WORLD, &W);

	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	D3DMATERIAL9 mtrl = d3d::InitMaterial(d3d::BLACK, d3d::BLACK, d3d::BLACK, d3d::BLACK, 0.0f);
	mtrl.Diffuse.a = 0.5f;

	Device->SetRenderState(D3DRS_ZENABLE, false);
	Device->SetMaterial(&mtrl);
	Device->SetTexture(0, 0);
	Teapot->DrawSubset(0);

	Device->SetRenderState(D3DRS_ZENABLE, true);
	Device->SetRenderState(D3DRS_STENCILENABLE, false);
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	Device->SetRenderState(D3DRS_STENCILENABLE, false);
}

void Cleanup()
{
	d3d::Release<IDirect3DVertexBuffer9*>(MirrorVB);
	d3d::Release<IDirect3DVertexBuffer9*>(WallVB);
	d3d::Release<IDirect3DVertexBuffer9*>(FloorVB);

	d3d::Release<IDirect3DTexture9*>(MirrorTex);
	d3d::Release<IDirect3DTexture9*>(WallTex);
	d3d::Release<IDirect3DTexture9*>(FloorTex);

	Teapot->Release();
}