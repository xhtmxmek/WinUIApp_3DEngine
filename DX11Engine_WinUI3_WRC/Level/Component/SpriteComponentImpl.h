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
		private:
			std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
		};
	}
}