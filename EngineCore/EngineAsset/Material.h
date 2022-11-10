#pragma once

namespace Engine
{
	namespace EngineAsset
	{
		class Texture;

		enum class TextureKey
		{
			Diffuse = 0,
			Normal,
			Specular,
			Texture_Max,

		};


		class Material
		{
		private:			
			vector<wil::com_ptr<Texture>> textures_;			
			void UpdateConstBuffers();
		public:
			Material();

			void SetTexture(TextureKey key, const wil::com_ptr<Texture>& texture)
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