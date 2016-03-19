#include "Input.h"

using namespace Toy3D;

Input::Input()
{

}

Input::~Input()
{

}

void Input::Initialize()
{
	for (auto& key : m_keys)
	{
		key = false;
	}
}

void Input::KeyDown(unsigned int key)
{
	m_keys[key] = true;
}

void Input::KeyUp(unsigned int key)
{
	m_keys[key] = false;
}

bool Input::IsKeyDown(unsigned int key)
{
	return m_keys[key];
}