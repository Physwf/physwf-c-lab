#ifndef _SCENE_H_
#define _SCENE_H_

#include "Object3D.h"
#include "Camera.h"

namespace Toy3D
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		void Initialize(int sw, int sh);
		const SP_Object& AddObject(const SP_Object& obj);
		const SP_Object& RemoveObject(const SP_Object& obj);

		void Update(unsigned int delta);
		void Render();
		void Dispose();
	private:
		object_set_t m_objSet;
		std::shared_ptr<Camera> m_spCamera;
	};
}
#endif