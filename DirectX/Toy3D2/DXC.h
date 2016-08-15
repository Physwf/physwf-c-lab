#pragma once

#include <d3d11.h>
#include <dxerr.h>



#define HR(x) \
		{							\
			HRESULT hr = (x);		\
			if(FAILED(hr))			\
			{														\
				return E_FAIL;										\
			}														\
		}

extern ID3D11Device* GDevice;
extern ID3D11DeviceContext* GImmediateContext;
extern IDXGISwapChain* GSwapChain;
extern UINT GMAXXQuality4x;
extern ID3D11RenderTargetView* GRenderTargetView;
extern ID3D11DepthStencilView* GDepthStencilView;

HRESULT InitDXC(HWND hWnd, int BufferWidth, int BufferHeight);
void RenderDXC();

