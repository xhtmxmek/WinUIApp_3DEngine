#pragma once

namespace Engine
{
	namespace EngineAsset
	{
		class Texture
		{
		public:
			Texture() : name_(L"") {};
			bool Load(const wstring& textureName);
			bool Load(const aiTexture* embeddedTexture);
			const wil::com_ptr<ID3D11ShaderResourceView>& GetShaderResourceView()
			{
				return shaderResourceView_;
			}
		private:
			wil::com_ptr<ID3D11Texture2D> texture2D_;
			wil::com_ptr<ID3D11ShaderResourceView> shaderResourceView_;
			std::wstring name_;
		};

		class TextureManager
		{
		public:
			static TextureManager& GetInstance()
			{
				static TextureManager instance;
				return instance;
			}

			void ReleaseInstance() { Textures.clear(); }

			TextureManager(const TextureManager&) = delete;
			TextureManager& operator=(const TextureManager&) = delete;

			std::optional<weak_ptr<Texture>> LoadTexture(const wstring& textureName, const aiScene* scene);
			std::optional<weak_ptr<Texture>> LoadTexture(const wstring& textureName);
		private:
			TextureManager(){}
			map< const wchar_t*, shared_ptr<Texture>> Textures;
		};
	}
}
