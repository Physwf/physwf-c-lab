//-----------------------------------------------------------------------------
// File:	BPatch.cpp
//
// Desc:	Bezier Patch class
//
// Based on code from aftershock, 
// Copyright (c) 1999 Stephen C. Taylor 
//
// I build this code with the help of a small and very instructive example,
// that I get from Bart Sekura. Thank you, Bart.
//
// Copyright (c) 2001 wolf@direct3d.net All rights reserved.
//-----------------------------------------------------------------------------
#ifndef __bpatch_h__
#define __bpatch_h__

#include <tchar.h>
#include <d3d8.h>
#include <d3dx8.h>

struct VERTICES {
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vNormal;
	D3DXVECTOR2 uv;
};

//-----------------------------------------------------------------------------
// Name: class CD3DPatch
// Desc: Class for creating and using Bezier Patches
//-----------------------------------------------------------------------------
class CD3DBPatch
{
public:
	TCHAR m_strName[512];
	
	DWORD m_dwULevel, m_dwVLevel;

	VERTICES* m_pvVertices;
	DWORD m_dwNumOfVertices;
	
	WORD* m_pwIndices;
	WORD m_wNumOfIndices;

	DWORD m_dwNumOfTriangles;

	LPDIRECT3DVERTEXBUFFER8 m_pVB;				// vertex buffer
	LPDIRECT3DINDEXBUFFER8  m_pIB;				// index buffer
	
public:
	VOID Create(CONST VERTICES* vControlPoints, DWORD dwUCount, DWORD dwVCount);
		
    HRESULT RestoreDeviceObjects( LPDIRECT3DDEVICE8 pd3dDevice );
    HRESULT InvalidateDeviceObjects();
	HRESULT DeleteDeviceObjects();
	HRESULT Render( LPDIRECT3DDEVICE8 pd3dDevice );
		
    
	CD3DBPatch(TCHAR* strName = _T("CD3DBPatch") );
};

#endif