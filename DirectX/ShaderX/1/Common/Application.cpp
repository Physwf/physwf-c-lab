#include "Application.h"
#include <sstream>

CD3DApplication::CD3DApplication()
{
	Instance = (this);
}

CD3DApplication::~CD3DApplication()
{

}

HRESULT CD3DApplication::Initialze(HINSTANCE hInstance, int nCmdShow)
{
	LoadString(hInstance, IDS_APP_TITLE, m_szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_RACORX, m_szWindowClass, MAX_LOADSTRING);
	m_hInst = hInstance;
	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow))
	{
		return S_FALSE;
	}
	HRESULT rc = OneTimeSceneInit();
	if (FAILED(rc)) {
		MessageBox(m_hWnd, L"OneTimeSceneInit error!",L"Error",0);
		return S_FALSE;
	}
	rc = InitDeviceObjects();
	if (FAILED(rc)) {
		MessageBox(m_hWnd, L"InitDeviceObjects error!", L"Error", 0);
		return S_FALSE;
	}
	return S_OK;
}

HRESULT CD3DApplication::CreateVSFromBinFile(IDirect3DDevice8* device, DWORD* dwDecl, TCHAR* strVSPath, DWORD* pHVS)
{
	TCHAR strFullPath[1024];
	TCHAR* strShortName;
	DWORD dwLen;

	dwLen = GetFullPathName(strVSPath, sizeof(strFullPath) / sizeof(TCHAR), strFullPath, &strShortName);

	if (dwLen == 0 || sizeof(strFullPath) / sizeof(TCHAR) <= dwLen) {
		MessageBox(m_hWnd, L"GetFullPathName Failed", L"Error", 0);
		return E_FAIL;
	}

	HANDLE hFile, hMap;
	char szBuffer[128];
	DWORD* pdwVS;
	HRESULT hr;

	hFile = CreateFile(strFullPath, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (INVALID_HANDLE_VALUE != hFile) {
		if (GetFileSize(hFile, 0) > 0) {
			hMap = CreateFileMapping(hFile, 0, PAGE_READONLY, 0, 0, 0);
		} else {
			CloseHandle(hFile);
			MessageBox(m_hWnd, L"CreateVSFromBinFile: File is empty!", L"Error", 0);
			return E_FAIL;
		}
	} else{
		MessageBox(m_hWnd, L"CreateVSFromBinFile: Can't Find file!", L"Error", 0);
		return E_FAIL;
	}
	pdwVS = (DWORD*)MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
	hr = device->CreateVertexShader(dwDecl, pdwVS, pHVS, 0);
	if (FAILED(hr)) {
		D3DXGetErrorStringA(hr, szBuffer, sizeof(szBuffer));
		MessageBox(m_hWnd, L"CreateVertexShader Failed!", L"Error", 0);
		return hr;
	}
	UnmapViewOfFile(pdwVS);
	CloseHandle(hMap);
	CloseHandle(hFile);
	return S_OK;
}

HRESULT CD3DApplication::CreateSphereMesh(LPDIRECT3DDEVICE8 pDevice, LPD3DXMESH* ppSphere)
{
	HRESULT hr;
	hr = D3DXCreateSphere(pDevice, 100.f, 40, 40, ppSphere, NULL);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"D3DXCreateSphere Failed!", L"Error", 0);
		return E_FAIL;
	}
	LPD3DXMESH pClone;
	hr = (*ppSphere)->CloneMeshFVF(D3DXMESH_MANAGED, D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX2 | D3DFVF_TEXCOORDSIZE2(0) | D3DFVF_TEXCOORDSIZE3(1), pDevice, &pClone);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"CloneMeshFVF Failed!", L"Error", 0);
		return E_FAIL;
	}
	hr = D3DXComputeNormals(pClone, NULL);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"D3DXComputeNormals Failed!", L"Error", 0);
		return E_FAIL;
	}
	struct Vertex
	{
		float x, y, z;
		D3DXVECTOR3 normal;
		float u, v;
		D3DXVECTOR3 tangent;
	};

	Vertex* pVertex = NULL;
	if (SUCCEEDED(pClone->LockVertexBuffer(D3DLOCK_DISCARD, reinterpret_cast<BYTE**>(&pVertex))))
	{
		DWORD numVertices = pClone->GetNumVertices();
		for (DWORD i = 0; i < numVertices; ++i)
		{
			D3DXVECTOR3 temp;
			D3DXVec3Normalize(&temp, &pVertex->normal);
			pVertex->u = atan2f(-temp.z, -temp.x) / (2.0f * D3DX_PI) + 0.5f;
			pVertex->v = 0.5f - asinf(-temp.y) / D3DX_PI;
			std::stringstream log;
			log << "x:" << pVertex->x << "\t\ty:" << pVertex->y << "\t\tz:" << pVertex->z << "\n";
			log << "nx:" << pVertex->normal.x << "\t\tny:" << pVertex->normal.y << "\t\tnz:" << pVertex->normal.z << "\n";
			log << "u:" << pVertex->u << "\t\tv:" << pVertex->v << "\n";
			if (pVertex->tangent.x != 0.0f || pVertex->tangent.y != 0.0f || pVertex->tangent.z != 0.0f)
				log << "tx:" << pVertex->tangent.x << "\t\tty:" << pVertex->tangent.y << "\t\ttz:" << pVertex->tangent.z << "\n";
			log << "--------------------------\n";
			OutputDebugStringA(log.str().c_str());
			++pVertex;
			
		}
		pClone->UnlockVertexBuffer();
	}
	LPD3DXMESH pOut = NULL;
	hr = D3DXComputeTangent(pClone, 0, pOut, 1, 1, true, NULL);
	if (FAILED(hr))
	{
		WCHAR szBuffer[512] = { 0 };
		D3DXGetErrorString(hr, szBuffer, sizeof(szBuffer));
		OutputDebugString(szBuffer);
		if (hr == D3DERR_INVALIDCALL) {
			MessageBox(m_hWnd, L"D3DXComputeTangent D3DERR_INVALIDCALL!", L"Error", 0);
		}
		else if (hr == E_OUTOFMEMORY) {
			MessageBox(m_hWnd, L"D3DXComputeTangent E_OUTOFMEMORY!", L"Error", 0);
		}
		return E_FAIL;
	}
	(*ppSphere)->Release();
	pClone->Release();
	ppSphere = &pOut;
	return S_OK;
}

BOOL CD3DApplication::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hwnd = CreateWindow(m_szWindowClass, m_szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	if (!hwnd)
	{
		DWORD error = GetLastError();
		return FALSE;
	}
	m_hWnd = hwnd;
	RECT size;
	GetWindowRect(m_hWnd, &size);
	m_iWidth = size.right - size.left;
	m_iHeight = size.bottom - size.top;
	ShowWindow(m_hWnd, nCmdShow);
	UpdateWindow(m_hWnd);

	return TRUE;
}

ATOM CD3DApplication::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RACORX));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_RACORX);
	wcex.lpszClassName = m_szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

LRESULT CD3DApplication::MessageHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		//m_spInput->KeyDown(static_cast<unsigned int>(wParam));
		return 0;
		break;
	case WM_KEYUP:
		return 0;
		break;
	default:
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}
	default:
	{
		return CD3DApplication::Instance->MessageHandler(hWnd, msg, wParam, lParam);
	}
	}
}

CD3DApplication* CD3DApplication::Instance = nullptr;

HRESULT CD3DApplication::Run()
{
	MSG msg;
	bool done = false, result = true;

	HACCEL hAccelTable;
	ZeroMemory(&msg, sizeof MSG);

	hAccelTable = LoadAccelerators(m_hInst, MAKEINTRESOURCE(IDC_RACORX));

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		Frame();
		Sleep(10);
	}
	return S_OK;
}

HRESULT CD3DApplication::ShutDown()
{
	DestroyWindow(m_hWnd);
	m_hWnd = NULL;
	m_hInst = NULL;
	return S_OK;
}
