#include "RacorX3.h"
#include <memory>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(pScmdline);

	using std::shared_ptr;
	using std::make_shared;
	shared_ptr<CD3DApplication> system = make_shared<RacorX3>();
	if (!system) return 0;
	HRESULT result = system->Initialze(hInstance, iCmdShow);
	if (result == S_OK)
		system->Run();

	return system->ShutDown();
}