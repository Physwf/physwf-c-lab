#include "Application.h"

class HelloShadowVolume : public CD3DApplication
{
public:
	HelloShadowVolume();
	~HelloShadowVolume();

	virtual HRESULT Run();
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
};