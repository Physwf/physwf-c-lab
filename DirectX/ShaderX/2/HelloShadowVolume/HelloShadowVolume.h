#include "Application.h"

struct Vertex
{
	float x, y, z;
	float nx, ny, nz;
};

class HelloShadowVolume : public CD3DApplication
{
public:
	HelloShadowVolume();
	~HelloShadowVolume();

	virtual HRESULT Frame();
protected:
	virtual HRESULT OneTimeSceneInit();
	virtual HRESULT InitDeviceObjects();
	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
	virtual HRESULT Render();
	virtual HRESULT FrameMove(FLOAT);
	virtual HRESULT FinalCleanup();

	virtual HRESULT CreateVolume(IDirect3DDevice8* pDevice, ID3DXMesh** ppOut);;
private:
	std::shared_ptr<IDirect3D8> m_spD3D;
	std::shared_ptr<IDirect3DDevice8> m_spDevice;

	D3DPRESENT_PARAMETERS m_dpps;

	std::shared_ptr<IDirect3DVertexBuffer8> m_spPlaneVB;
	std::shared_ptr<IDirect3DIndexBuffer8> m_spPlaneIB;
	DWORD m_dwPlaneNumVertices;
	DWORD m_dwPlaneNumFaces;
	DWORD m_dwPlaneVSH;
	DWORD m_dwPlanePSH;
	D3DXVECTOR4 m_cPlaneTint;

	D3DXMATRIX m_mtPlaneWorld;

	std::shared_ptr<IDirect3DVertexBuffer8> m_spVolumeVB;
	std::shared_ptr<IDirect3DIndexBuffer8> m_spVolumeIB;
	DWORD m_dwVolumeNumVertices;
	DWORD m_dwVolumeNumFaces;
	DWORD m_dwVolumeVSH;
	DWORD m_dwVolumePSH;

	D3DXMATRIX m_mtVolumeWorld;
	D3DXVECTOR4 m_cVolumeTint;

	D3DXMATRIX m_mtView;
	D3DXMATRIX m_mtProj;

};