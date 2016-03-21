#include "Vertex.h"

using namespace Toy3D;

const DWORD Vertex::FVF = D3DFVF_XYZ;

const DWORD ColorVertex::FVF_COLOR = D3DFVF_XYZ | D3DFVF_DIFFUSE;

const DWORD TexVertex::FVF_TEX = D3DFVF_XYZ | D3DFVF_TEX0;

const DWORD SkyBoxVertex::FVF_SKYBOX = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);
