#ifndef _D3D_UTITILY_H
#define _D3D_UTITILY_H
#include <d3d9.h>

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
}
#endif