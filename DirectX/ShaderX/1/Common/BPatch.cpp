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
// Copyright (c) 2002 wolf@direct3d.net All rights reserved.
//-----------------------------------------------------------------------------
#define STRICT
#include <stdio.h>
#include <d3d8.h>
#include <d3dx8.h>
#include "dxutil.h"

#include "BPatch.h"

//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
CD3DBPatch::CD3DBPatch( TCHAR* strName )
{
	wcscpy_s(m_strName, strName);
	m_dwULevel = NULL;
	m_dwVLevel = NULL;
	m_pvVertices = NULL;
	m_dwNumOfVertices = NULL;
	m_pwIndices = NULL;
	m_wNumOfIndices = NULL;
	m_dwNumOfTriangles = NULL;	
    m_pVB  = NULL;
	m_pIB  = NULL;
}

//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
VOID FillCurve(DWORD dwStep, DWORD dwSize, DWORD dwStride, VERTICES* pvVertices)
{
    while(dwStep>0) {
        int halfstep = dwStep / 2;
        int doublestep = dwStep * 2;
        for(DWORD i = 0; i < dwSize - 1; i += doublestep) 
		{
            int left = i * dwStride;
            int mid = (i + dwStep) * dwStride;
            int right = (i + doublestep) * dwStride;
			
            // lerp vertex position
			D3DXVECTOR3 a,b;
			D3DXVec3Lerp(&a, &pvVertices[left].vPosition, &pvVertices[mid].vPosition, 0.5f);
			D3DXVec3Lerp(&b, &pvVertices[mid].vPosition, &pvVertices[right].vPosition, 0.5f);
			D3DXVec3Lerp(&pvVertices[mid].vPosition, &a, &b, 0.5f);
            
            if(halfstep>0) 
			{
                int half_left = (i+halfstep) * dwStride;
                int half_right = (i+halfstep*3) * dwStride;
				
                pvVertices[half_left].vPosition = a;
                pvVertices[half_right].vPosition = b;
            }
			
            // texture coords
			D3DXVECTOR2 u,v;
			D3DXVec2Lerp(&u, &pvVertices[left].uv, &pvVertices[mid].uv, 0.5f);
			D3DXVec2Lerp(&v, &pvVertices[mid].uv, &pvVertices[right].uv, 0.5f);
			D3DXVec2Lerp(&pvVertices[mid].uv, &u, &v, 0.5f);
            
            if(halfstep>0) {
                int half_left = (i+halfstep) * dwStride;
                int half_right = (i+halfstep*3) * dwStride;
				
                pvVertices[half_left].uv = u;
                pvVertices[half_right].uv = v;
            }
        }
        dwStep = halfstep;
    }
}

//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
VOID ComputeNormals (VERTICES *pvVertices, WORD* pwIndices, 
					 DWORD dwNumOfTriangles, DWORD dwNumOfVertices)
{
    // compute face normals
    // for every triangle, take three vertices and cross the edges
	D3DXVECTOR3* pvFaceNormals;
	pvFaceNormals = new D3DXVECTOR3[dwNumOfTriangles];

    for(DWORD i = 0; i < dwNumOfTriangles; ++i) 
	{
        int e0=pwIndices[i*3+0];
        int e1=pwIndices[i*3+1];
        int e2=pwIndices[i*3+2];
		
        D3DXVECTOR3 v0 = pvVertices[e0].vPosition;
        D3DXVECTOR3 v1 = pvVertices[e1].vPosition;
        D3DXVECTOR3 v2 = pvVertices[e2].vPosition;
		
		D3DXVECTOR3 edge1 = v1-v0;
		D3DXVECTOR3 edge2 = v2-v0;
		
		D3DXVec3Cross(&pvFaceNormals[i],&edge1,&edge2);
		D3DXVec3Normalize(&pvFaceNormals[i],&pvFaceNormals[i]);
    }
	
    for(DWORD c = 0; c < dwNumOfVertices; ++c) 
	{
		D3DXVECTOR3 v=pvVertices[c].vPosition;
		D3DXVECTOR3 sum(0,0,0);
        int shared=0;
		
        for(DWORD i = 0; i < dwNumOfTriangles; ++i) 
		{
            int e0=pwIndices[i*3+0];
            int e1=pwIndices[i*3+1];
            int e2=pwIndices[i*3+2];
			
            D3DXVECTOR3 v0 = pvVertices[e0].vPosition;
            D3DXVECTOR3 v1 = pvVertices[e1].vPosition;
            D3DXVECTOR3 v2 = pvVertices[e2].vPosition;
			
            if(v0==v||v1==v||v2==v) 
			{
                sum+=pvFaceNormals[i];
                ++shared;
            }
        }

		pvVertices[c].vNormal=sum/(float)shared;
		D3DXVec3Normalize(&pvVertices[c].vNormal,&pvVertices[c].vNormal);
    }
	SAFE_DELETE (pvFaceNormals);
}

//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
VOID CD3DBPatch::Create(CONST VERTICES* vControlPoints, DWORD dwUCount, DWORD dwVCount)
{
	// calculate total number of points we need after tessellation
	// based on the level and number of control points
	DWORD dwUSize = (1<<(m_dwULevel+1))*((dwUCount-1)>>1) + 1;
	DWORD dwVSize = (1<<(m_dwVLevel+1))*((dwVCount-1)>>1) + 1; 
	m_dwNumOfVertices = dwUSize * dwVSize;
	
	DWORD dwUStep = (dwUSize-1)/(dwUCount-1);
	DWORD dwVStep = (dwVSize-1)/(dwVCount-1);
	
	// fill sparse control points
	m_pvVertices = new VERTICES[m_dwNumOfVertices];
	CONST VERTICES* vSparseControlPoints = vControlPoints;

	DWORD dwU, dwV;
	for(dwV = 0; dwV < dwVSize; dwV += dwVStep) 
	{
		for(dwU = 0; dwU < dwUSize; dwU += dwUStep) 
		{
			int i = dwV * dwUSize + dwU;
			m_pvVertices[i]= *vSparseControlPoints++;
		}
	}
	
	// now fill out the rest
	for(dwU = 0; dwU < dwUSize; dwU += dwUStep) 
	{
		FillCurve(dwVStep, dwVSize, dwUSize, m_pvVertices + dwU);
	}
	for(dwV = 0; dwV < dwVSize; ++dwV) 
	{
		FillCurve(dwUStep, dwUSize, 1, m_pvVertices + dwV * dwUSize);
	}
	
	// setup triangles (indices)
	m_wNumOfIndices = (WORD)((dwUSize - 1)*(dwVSize - 1) * 6);
	m_dwNumOfTriangles = m_wNumOfIndices/3;
	m_pwIndices = new WORD[m_wNumOfIndices];
	
	// build triangles 
	WORD* pwIndices = m_pwIndices;
	for(dwV = 0; dwV < dwVSize - 1; ++dwV) 
	{
		for(dwU = 0; dwU < dwUSize - 1; ++dwU) 
		{
			// get a quad and build two tris out of it
			//  v0--v1
			//  |   |
			//  v2--v3
			int v0 = dwV * dwUSize + dwU;
			int v1 = v0+1;
			int v2 = (dwV + 1) * dwUSize + dwU;
			int v3 = v2+1;
			
			pwIndices[0] = v0, pwIndices[1] = v1, pwIndices[2] = v3;
			pwIndices[3] = v3, pwIndices[4] = v2, pwIndices[5] = v0;
            
			pwIndices += 6; //next two tris        
		}
	}
	// compute the normals
	ComputeNormals (m_pvVertices, m_pwIndices, 
					m_dwNumOfTriangles, m_dwNumOfVertices);
}


//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
HRESULT CD3DBPatch::RestoreDeviceObjects( LPDIRECT3DDEVICE8 pd3dDevice )
{

	// Declare custom FVF macro.
	#define D3DFVF_VERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

	// Create the vertex buffer
    if( FAILED( pd3dDevice->CreateVertexBuffer(m_dwNumOfVertices * sizeof(VERTICES),
												D3DUSAGE_WRITEONLY , 
												D3DFVF_VERTEX, 
												D3DPOOL_MANAGED, 
												&m_pVB ) ) )
			return E_FAIL;
	
    // lock and unlock the vertex buffer to fill it with memcpy
    VOID* pVertices;
    if( FAILED( m_pVB->Lock( 0, m_dwNumOfVertices * sizeof(VERTICES), 
		(BYTE**)&pVertices, 0 ) ) )
        return E_FAIL;
    memcpy( pVertices, m_pvVertices, m_dwNumOfVertices * sizeof(VERTICES));
    m_pVB->Unlock();
	
	// create and fill the index buffer
	if(FAILED (pd3dDevice->CreateIndexBuffer(m_wNumOfIndices * sizeof (WORD), 0, 
								D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB)))
								return E_FAIL;
	
	// fill index buffer
	VOID *pIndices;
	if (FAILED(m_pIB->Lock(0, m_wNumOfIndices * sizeof (WORD), 
		(BYTE **)&pIndices, 0)))
		return E_FAIL;
	memcpy(pIndices, m_pwIndices, m_wNumOfIndices * sizeof (WORD));
	m_pIB->Unlock();
	
  return S_OK;
}


//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
HRESULT CD3DBPatch::InvalidateDeviceObjects()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pIB);
   return S_OK;
}

//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
HRESULT CD3DBPatch::DeleteDeviceObjects()
{
	SAFE_DELETE(m_pvVertices);
	SAFE_DELETE(m_pwIndices);
  return S_OK;
}

//-----------------------------------------------------------------------------
// Name:
// Desc:
//-----------------------------------------------------------------------------
HRESULT CD3DBPatch::Render( LPDIRECT3DDEVICE8 pd3dDevice )
{
	// set the vertex buffer
	// == specify the source of stream 0
	pd3dDevice->SetStreamSource(0,m_pVB, sizeof(VERTICES));
	pd3dDevice->SetIndices(m_pIB,0);

	// ... rendering
	pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
									0,
									m_dwNumOfVertices,
									0,
									m_dwNumOfTriangles);
	return S_OK;
}

	
	


