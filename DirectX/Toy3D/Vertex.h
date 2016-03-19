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
		Vertex(const Vertex& rhs) = default;
		Vertex& operator=(const Vertex& rhs) = default;
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
}
#endif