#pragma once

namespace Engine
{
	namespace EngineAsset
	{
		class TextureManager
		{
		public:
			static TextureManager& GetInstance()
			{
				static TextureManager instance;
				return instance;
			}

			TextureManager(const TextureManager&) = delete;
			TextureManager& operator=(const TextureManager&) = delete;

			const shared_ptr<Texture>& GetTexture(winrt::hstring textureName)
			{
				auto iter = Textures.find(textureName);
				if (iter != Textures.end())
				{
					return iter->second;
				}
				else
				{
					auto newTexture = make_shared<Texture>();
					Textures.insert(make_pair(textureName, newTexture));
					return newTexture;
				}
			}
		private:
			TextureManager();
			map< winrt::hstring, shared_ptr<Texture>> Textures;
		};

		class Texture
		{
		public:
			Texture() : Name(L"") {};
			bool Load(const wstring& textureName);
			const winrt::com_ptr<ID3D11ShaderResourceView>& GetShaderResourceView()
			{
				return ShaderResourceView;
			}
		private:
			winrt::com_ptr<ID3D11ShaderResourceView> ShaderResourceView;
			std::wstring Name;
		};
	}
}
