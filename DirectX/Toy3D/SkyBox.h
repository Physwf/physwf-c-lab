#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "Object3D.h"
#include "Camera.h"

namespace Toy3D
{
	class SkyBox : public Object3D
	{
	public:
		explicit SkyBox(std::shared_ptr<Camera> c) : m_spCamera(c){ }
		~SkyBox();

		virtual void Update(unsigned int delta) override;
		virtual void Render() override;

		static std::shared_ptr<SkyBox> Create(std::shared_ptr<Camera> c,const char* file);
	protected:
		virtual void AlllocateBuffers() override;
	private:
		std::shared_ptr<Camera> m_spCamera;
		std::shared_ptr<IDirect3DCubeTexture9> m_spCubeTexture{nullptr};
		bool m_bDirty;
	};

}
#endif