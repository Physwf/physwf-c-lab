#include "Scene.h"

using namespace Toy3D;

Scene::Scene()
{
}

Scene::~Scene()
{

}

void Scene::Update(unsigned int delta)
{
	m_spCamera->Yaw(0.01f);
	m_spCamera->Update(delta);
	m_spSky->Update(delta);
	for (auto& obj : m_objSet)
		obj->Update(delta);
}

void Scene::Render()
{
	d3dContext->Clear();
	d3dContext->BeginScene();
	m_spCamera->Render();
	m_spSky->Render();

	for (auto& obj : m_objSet)
		obj->Render();
	d3dContext->EndScene();
	d3dContext->Present();
}

void Scene::Initialize(int sw, int sh)
{
	m_spCamera = std::make_shared<Camera>(sw, sh);
	m_spCamera->SetPosition(0.0f, 0.0f, -5.0f);
	m_spCamera->SetViewport(0, 0, sw, sh, 0, 1);
	D3DXVECTOR3 target(0.0f,0.0f,0.0f);
	m_spCamera->LookAt(&target);
	//m_spCamera->Rotate(D3DX_PI / 2, 0.0f,0.0f);
	m_spSky = SkyBox::Create(m_spCamera, "sky.dds");
	d3dContext->SetRenderState(D3DRS_LIGHTING, false);//to be reconsider+
}

const SP_Object& Toy3D::Scene::AddObject(const SP_Object& obj)
{
	m_objSet.insert(obj);
	return obj;
}

const SP_Object& Toy3D::Scene::RemoveObject(const SP_Object& obj)
{
	m_objSet.erase(obj);
	return obj;
}

void Scene::Dispose()
{

}
