#pragma once

#include "Application.h"
#include "BPatch.h"
#include "d3dutil.h"
#include <memory>

struct ShaderVertex
{
	FLOAT x, y, z;
	FLOAT nx, ny, nz;
	FLOAT u, v;
	FLOAT bx, by, bz;
};

struct SimpleVertex
{
	FLOAT x, y, z;
};

void LightEval(D3DXVECTOR4 *cool, D3DXVECTOR2 *input, D3DXVECTOR2 *sampleSize, void *pfPower);

class RacorX8 : public CD3DApplication 
{
public:
	RacorX8();
	~RacorX8();

	virtual HRESULT Frame();

protected:
	virtual HRESULT ConfirmDevice(D3DCAPS8* pCaps, DWORD dwBehavior, D3DFORMAT Format);
	virtual HRESULT OneTimeSceneInit();
	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT Render();
	virtual HRESULT FrameMove(FLOAT);
	virtual HRESULT FinalCleanup();

	virtual HRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
private:
	HRESULT CreateSphere();
	HRESULT LoadXFile(const LPSTR name);

private:
	std::shared_ptr<IDirect3D8> m_spD3D;
	std::shared_ptr<IDirect3DDevice8> m_spDevice;
	D3DCAPS8 m_D3DCaps;
	D3DPRESENT_PARAMETERS m_dpps;
	int m_iVP;
	D3DVIEWPORT8 m_Viewport;

	
	std::shared_ptr<IDirect3DTexture8> m_spColorMap;
	std::shared_ptr<IDirect3DTexture8> m_spHeightMap;
	std::shared_ptr<IDirect3DTexture8> m_spNormalMap;
	std::shared_ptr<IDirect3DTexture8> m_spPower;

	std::shared_ptr<ID3DXMesh> m_spEarthMesh;

	std::shared_ptr<IDirect3DVertexBuffer8> m_spVB;
	std::shared_ptr<IDirect3DIndexBuffer8> m_spIB;

	std::shared_ptr<IDirect3DVertexBuffer8> m_spVBNormal;
	std::shared_ptr<IDirect3DIndexBuffer8> m_spIBNormal;
	std::shared_ptr<IDirect3DVertexBuffer8> m_spVBTangent;
	std::shared_ptr<IDirect3DIndexBuffer8> m_spIBTangent;

	int m_iNumTriangles, m_iNumVertices;

	DWORD m_dwVSH;
	DWORD m_dwPSH;
	DWORD m_dwPSHBump;
	DWORD m_dwPSHBump14;

	DWORD m_dwVSHLine;
	DWORD m_dwVPHLine;

	D3DXMATRIX m_mtWorld;
	D3DXMATRIX m_mtView;
	D3DXMATRIX m_mtProj;

	CD3DArcBall m_ArcBall;

	D3DXVECTOR3 m_vObjectCenter{ 0.0f, 0.0f, 0.0f };
	float m_fZDist{0.0f};
	float m_fObjectRadius;
	char m_bKey[256];

	bool m_bPS14Avaliable{ true };
	bool m_bBump{ FALSE };
	bool m_bPixelShader{ FALSE };
	bool m_bShowNormal{ FALSE };
	bool m_bShowTangent{ FALSE };
};