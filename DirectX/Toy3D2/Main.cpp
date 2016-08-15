#include "Application.h"
#include <memory>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdShow)
{
	using Toy3D::Application;
	using std::shared_ptr;
	using std::make_shared;

	shared_ptr<Application> sp_App = make_shared<Application>();
	bool result;

	if (!sp_App) return 1;
	result = sp_App->Initialize();
	if (result)
		sp_App->Run();

	sp_App->Shutdown();

	return 0;
}