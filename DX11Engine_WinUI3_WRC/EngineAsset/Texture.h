#pragma once

namespace Engine
{
	namespace EngineAsset
	{
		class Texture
		{
		public:
			Texture() : Name(L"") {};
			bool Load(const winrt::hstring& textureName);
			const winrt::com_ptr<ID3D11ShaderResourceView>& GetShaderResourceView()
			{
				return ShaderResourceView;
			}
		private:
			winrt::com_ptr<ID3D11ShaderResourceView> ShaderResourceView;
			std::wstring Name;
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

			const shared_ptr<Texture>& GetTexture(winrt::hstring textureName)
			{	
				wstring applicationPath = Path::ApplicationDir;				
				winrt::hstring path = applicationPath + L"\\Assets\\" + textureName;

				auto iter = Textures.find(path);
				if (iter != Textures.end())
				{
					return iter->second;
				}
				else
				{
					auto newTexture = make_shared<Texture>();
					newTexture->Load(path);
					Textures.insert(make_pair(path, newTexture));
					return Textures[path];
					//요거 고쳐야됨
				}
			}
		private:
			TextureManager(){}
			map< winrt::hstring, shared_ptr<Texture>> Textures;
		};
	}
}
