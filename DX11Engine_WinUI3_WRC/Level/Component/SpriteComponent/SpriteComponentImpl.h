#pragma once

namespace Engine
{
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
			void SetPosition(Vector2 screenPos) { ScreenPos = screenPos; }
		private:
			//property로 빼는건 나중에
			Vector2 ScreenPos;
			float Rotation;
			float Scale;

			Vector2 UVOffset;
			Color TintColor;
			winrt::com_ptr<ID3D11ShaderResourceView> m_texture;
			//Colors::WH
			std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
		};
	}
}