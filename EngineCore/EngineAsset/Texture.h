#pragma once

namespace Engine
{
	namespace EngineAsset
	{
		class Texture
		{
		public:
			Texture() : Name(L"") {};
			bool Load(const wstring& textureName);
			const wil::com_ptr<ID3D11ShaderResourceView>& GetShaderResourceView()
			{
				return ShaderResourceView;
			}
		private:
			wil::com_ptr<ID3D11ShaderResourceView> ShaderResourceView;
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

			const shared_ptr<Texture>& GetTexture(const wstring& textureName)
			{	
				wstring applicationPath = Path::EngineDir;				
				wstring path = applicationPath + L"\\Assets\\" + textureName;

				auto iter = Textures.find(path.c_str());
				if (iter != Textures.end())
				{
					return iter->second;
				}
				else
				{
					auto newTexture = make_shared<Texture>();
					newTexture->Load(path);
					Textures.insert(make_pair(path.c_str(), newTexture));
					return Textures[path.c_str()];
				}
			}
		private:
			TextureManager(){}
			map< const wchar_t*, shared_ptr<Texture>> Textures;
		};
	}
}
