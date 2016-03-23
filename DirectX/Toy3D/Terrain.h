#ifndef _TERRAIN_H_
#define _TERRAIN_H_

#include "Object3D.h"

namespace Toy3D
{
	struct TerrainDesc
	{
		UINT Width;
		UINT Depth;
		UINT Height;
		UINT HeightMapWidth;
		UINT HeightMapHeight;
		const char* HeightMapPath;
		const char* TexturePath;
	};

	class Terrain : public Object3D
	{
	public:
		Terrain(UINT Width, UINT Leght, UINT Height, UINT hmWidth, UINT hmHeight);
		Terrain(const Terrain& rhs) = delete;
		~Terrain() = default;

		static std::shared_ptr<Terrain> Create(const TerrainDesc* desc);

		void Initialize(const char* rawfile, const char* texfile);

		virtual void Update(unsigned int delta) override;
		virtual void Render() override;

	protected:
		virtual void AlllocateBuffers() override;
	private:
		void computeVertices(TexVertex* vertices);
		void computeVertices(TexNormalVertex* vertices);
		template <typename T> void computeIndices(T* indices,D3DPRIMITIVETYPE Type);
	private:
		UINT m_uWidth{ 0 };
		UINT m_uDepth{ 0 };
		UINT m_uHeight{ 0 };
		UINT m_uHeightMapWidth{ 0 };
		UINT m_uHeightMapHeight{ 0 };
		std::unique_ptr<UCHAR[]> m_spHeightMap;
		std::shared_ptr<IDirect3DTexture9> m_spTexture;
		UINT m_uNumVertices{ 0 };
		UINT m_uNumTriangles{ 0 };
		bool m_bDirty;
	};

	template <typename T> void Terrain::computeIndices(T* indices, D3DPRIMITIVETYPE Type)
	{
		int Base = 0;
		UINT numVertsX = m_uHeightMapWidth + 1;
		UINT numVertsZ = m_uHeightMapHeight + 1;
		if (Type == D3DPT_TRIANGLELIST)
		{
			for (UINT i = 0; i < m_uHeightMapHeight; ++i)
			{
				for (UINT j = 0; j < m_uHeightMapWidth; ++j)
				{
					indices[Base] = i * numVertsX + j;
					indices[Base + 1] = i * numVertsX + j + 1;
					indices[Base + 2] = (i + 1) * numVertsX + j;

					indices[Base + 3] = (i + 1) * numVertsX + j;
					indices[Base + 4] = i * numVertsX + j + 1;
					indices[Base + 5] = (i + 1) * numVertsX + j + 1;

					Base += 6;
				}
			}
		}
		else if (Type == D3DPT_TRIANGLESTRIP)
		{

		}
	}
}
#endif