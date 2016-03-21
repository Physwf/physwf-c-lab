#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <d3d9.h>
#include <windows.h>

namespace Toy3D
{
	struct Vertex
	{
		Vertex() = default;
		Vertex(float x, float y, float z) :mX(x), mY(y), mZ(z) { }
		static const DWORD FVF;
		float mX{ 0.0f }, mY{ 0.0f }, mZ{ 0.0f };
	};

	struct ColorVertex : public Vertex
	{
		ColorVertex() = default;
		ColorVertex(float x, float y, float z, D3DCOLOR color) :Vertex(x,y,z), m_Color(color){}
		D3DCOLOR m_Color{ 0 };
		static const DWORD FVF_COLOR;
	};

	struct TexVertex : public Vertex
	{
		TexVertex(float x, float y, float z, float u, float v) :Vertex(x, y, z), mU(u), mV(v){}
		float mU{ 0.0 }, mV{ 0.0 };
		static const DWORD FVF_TEX;
	};

	struct SkyBoxVertex : public Vertex
	{
		SkyBoxVertex(float x, float y, float z, float u, float v, float t) :Vertex(x, y, z), mU(u), mV(v), mT(t) {}
		float mU{ 0.0f }, mV{ 0.0f }, mT{ 0.0f };
		static const DWORD FVF_SKYBOX;
	};
}
#endif