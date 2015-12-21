#ifndef _D3D_UTITILY_H
#define _D3D_UTITILY_H
#include <d3d9.h>
#include <d3dx9.h>

namespace d3d {
	bool InitD3D(
		HWND hwnd,
		int width, int height,
		bool windowed,
		D3DDEVTYPE deviceType,
		IDirect3DDevice9** device);

	int EnterMsgLoop(
		bool(*ptr_display)(float timeDelta));

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	template<class T> void Release(T t) {
		if (t)
		{
			t->Release();
			t = 0;
		}
	}

	template <class T> void Delete(T t) {
		delete t;
		t = 0;
	}

	const D3DXCOLOR WHITE(D3DCOLOR_XRGB(255, 255, 255));
	const D3DXCOLOR BLACK(D3DCOLOR_XRGB(0, 0, 0));
	const D3DXCOLOR RED(D3DCOLOR_XRGB(255, 0, 0));
	const D3DXCOLOR GREEN(D3DCOLOR_XRGB(0, 255, 0));
	const D3DXCOLOR BLUE(D3DCOLOR_XRGB(0, 0, 255));
	const D3DXCOLOR YELLOW(D3DCOLOR_XRGB(255, 255, 0));
	const D3DXCOLOR CYAN(D3DCOLOR_XRGB(0, 255, 255));
	const D3DXCOLOR MAGENTA(D3DCOLOR_XRGB(255, 0, 255));

	D3DMATERIAL9 InitMaterial(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);

	const D3DMATERIAL9 WHITE_MTRL = InitMaterial(WHITE, WHITE, WHITE, BLACK, 8.0f);
	const D3DMATERIAL9 RED_MTRL = InitMaterial(RED, RED, RED, BLACK, 8.0f);
	const D3DMATERIAL9 GREEN_MTRL = InitMaterial(GREEN, GREEN, GREEN, BLACK, 8.0f);
	const D3DMATERIAL9 BLUE_MTRL = InitMaterial(BLUE, BLUE, BLUE, BLACK, 8.0f);
	const D3DMATERIAL9 YELLOW_MTRL = InitMaterial(YELLOW, YELLOW, YELLOW, BLACK, 8.0f);

	D3DLIGHT9 InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color);
	D3DLIGHT9 InitPointLight(D3DXVECTOR3* position, D3DXCOLOR* color);
	D3DLIGHT9 InitSpotLight(D3DXVECTOR3* position, D3DXVECTOR3* direction, D3DXCOLOR* color);

}
#endif