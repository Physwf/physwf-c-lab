#include "Demo.h"

IDirect3DDevice9* Device = 0;

bool Setup()
{
	return true;
}

void Cleanup()
{

}

bool Display(float timeDelta)
{
	if (Device)
	{
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,0x00000000, 1.0f, 0);
		Device->Present(0, 0, 0, 0);
	}
	return true;
}