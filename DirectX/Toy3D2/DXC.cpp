#include "DXC.h"

ID3D11Device* GDevice;
ID3D11DeviceContext* GImmediateContext;
IDXGISwapChain* GSwapChain;
UINT GMAXXQuality4x;
ID3D11RenderTargetView* GRenderTargetView;
ID3D11Texture2D* GDepthStencilBuffer;
ID3D11DepthStencilView* GDepthStencilView;
FLOAT GClearColor[] = { 0.0f,0.0f,0.6f,0.0f };

HRESULT InitDXC(HWND hWnd, int BufferWidth, int BufferHeight)
{
	/*Create Device*/
	D3D_FEATURE_LEVEL FetureLevels[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	D3D_FEATURE_LEVEL FeatureLevel;
	HR(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, FetureLevels, 3, D3D11_SDK_VERSION, &GDevice, &FeatureLevel, &GImmediateContext));
	if (FeatureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		return E_FAIL;
	}
	/*Check MSAA Level*/
	HR(GDevice->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &GMAXXQuality4x));
	/*Create Swap Chain*/
	IDXGIDevice* dxgiDevice = 0;
	GDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
	IDXGIAdapter* dxgiAdapter = 0;
	dxgiDevice->GetParent(__uuidof(dxgiAdapter), (void**)&dxgiAdapter);
	IDXGIFactory* dxgiFactory;
	dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory);

	DXGI_SWAP_CHAIN_DESC SwapChainDesc;

	SwapChainDesc.BufferDesc.Width = BufferWidth;
	SwapChainDesc.BufferDesc.Height = BufferHeight;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	SwapChainDesc.SampleDesc.Count = 4;
	SwapChainDesc.SampleDesc.Quality = GMAXXQuality4x - 1;

	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.OutputWindow = hWnd;
	SwapChainDesc.Windowed = true;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SwapChainDesc.Flags = 0;

	HR(dxgiFactory->CreateSwapChain(GDevice, &SwapChainDesc, &GSwapChain));

	dxgiDevice->Release();
	dxgiAdapter->Release();
	dxgiFactory->Release();

	/*Create Render Target View*/
	ID3D11Texture2D* BackBuffer;
	HR(GSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackBuffer)));
	HR(GDevice->CreateRenderTargetView(BackBuffer, 0, &GRenderTargetView));
	BackBuffer->Release();

	/*Create Depth/Stencil Target View*/
	D3D11_TEXTURE2D_DESC ResDesc;
	ResDesc.Width = BufferWidth;
	ResDesc.Height = BufferHeight;
	ResDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	ResDesc.MipLevels = 1;
	ResDesc.ArraySize = 1;
	ResDesc.Usage = D3D11_USAGE_DEFAULT;
	ResDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	ResDesc.CPUAccessFlags = 0;
	ResDesc.MiscFlags = 0;
	ResDesc.SampleDesc.Count = 4;
	ResDesc.SampleDesc.Quality = GMAXXQuality4x - 1;

	HR(GDevice->CreateTexture2D(&ResDesc, 0, &GDepthStencilBuffer));
	HR(GDevice->CreateDepthStencilView(GDepthStencilBuffer, 0, &GDepthStencilView));

	GImmediateContext->OMSetRenderTargets(1, &GRenderTargetView, GDepthStencilView);

	D3D11_VIEWPORT ViewPort;
	ViewPort.TopLeftX = 0;
	ViewPort.TopLeftY = 0;
	ViewPort.Width = (float)BufferWidth;
	ViewPort.Height = (float)BufferHeight;
	ViewPort.MinDepth = 0.0f;
	ViewPort.MaxDepth = 1.0f;

	GImmediateContext->RSSetViewports(1, &ViewPort);

	return S_OK;
}

void RenderDXC()
{
	GImmediateContext->ClearRenderTargetView(GRenderTargetView, GClearColor);
	GImmediateContext->ClearDepthStencilView(GDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	GSwapChain->Present(0, 0);
}
