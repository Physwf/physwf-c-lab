#include "Application.h"

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

private:
	std::shared_ptr<IDirect3D8> m_spD3D;
	std::shared_ptr<IDirect3DDevice8> m_spDevice;

	D3DPRESENT_PARAMETERS m_dpps;

	std::shared_ptr<ID3DXMesh> m_spHerizonPlane;
	DWORD m_dwPlaneVSH;
	DWORD m_dwPlanePSH;
	D3DXVECTOR4 m_cPlaneTint;

	D3DXMATRIX m_mtView;
	D3DXMATRIX m_mtProj;

};