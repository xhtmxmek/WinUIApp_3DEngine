#pragma once

namespace Engine
{
	namespace EngineAsset
	{
		class Texture;
	}

	namespace Component
	{
		class SpriteComponentImpl
		{
		public:
			SpriteComponentImpl(const std::string& name);
			void Init();
			void Tick(float elasedTime);
			void Draw();
			void Load(const winrt::hstring& textureName);	
			//GET_SET_ACCESSOR(Vector2, ScreenPos);
			//GET_SET_ACCESSOR(float, Rotation);
			//GET_SET_ACCESSOR(float, Scale);			
		private:
			//property로 빼는건 나중에
			Vector2 ScreenPos;
			float Rotation;
			float Scale;

			Vector2 UVOffset;
			Color TintColor;
			shared_ptr<EngineAsset::Texture> BasicTexture;
			//Colors::WH
			std::unique_ptr<DirectX::SpriteBatch> SpriteBatch;
		};
	}
}