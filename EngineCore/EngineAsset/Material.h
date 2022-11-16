#pragma once

namespace Engine
{
	namespace EngineAsset
	{
		class Texture;

		enum TextureKey
		{
			DiffuseMap = 0,
			NormalMap,
			SpecularMap,
			Texture_Max,

		};


		class Material
		{
		private:			
			vector<std::shared_ptr<Texture>> textures_;			
			void UpdateConstBuffers();
		public:
			Material();

			void SetTexture(TextureKey key, const std::shared_ptr<Texture>& texture)
			{
				int textureKey = static_cast<int>(key);
				textures_[textureKey] = texture;
			}

			void DrawMaterial();
		};

		class MaterialManager
		{
		public:
			//MaterialManager& GetInstance()
			//{
			//}
		private:
			MaterialManager();
			std::map<const wchar_t*, std::shared_ptr<Material>> Materials;			
		};
	}
}