#pragma once
namespace Engine
{
	namespace EngineAsset
	{
		class Material;
	}
	namespace Renderer
	{
		class MaterialDrawer
		{
		public:
			static void DrawMaterial(const weak_ptr<EngineAsset::Material>& material);
		private:
			static void UpdateConstBuffers();
		};
	}
}