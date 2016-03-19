#include "Application.h"
#include <memory>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdShow)
{
	using Toy3D::Application;
	using std::shared_ptr;
	using std::make_shared;
	//using shared_ptr
	shared_ptr<Application> system;
	bool result;

	system = make_shared<Application>();
	if (!system) return 0;
	result = system->Initialize();
	if (result)
		system->Run();

	system->Shutdown();

	/*
	//using unique_ptr
	using std::unique_ptr;
	unique_ptr<System> uSystem(new System());
	result = uSystem->Initialize();
	if (result)
		uSystem->Run();

	uSystem->Shutdown();
	*/

	return 0;
}