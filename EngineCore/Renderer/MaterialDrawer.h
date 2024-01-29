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
			void DrawMaterial(const weak_ptr<EngineAsset::Material>& material);
		private:
			std::shared_ptr<GraphicsLibrary::ShaderObject> drawShader_;
			static void UpdateConstBuffers();
		};
	}
}