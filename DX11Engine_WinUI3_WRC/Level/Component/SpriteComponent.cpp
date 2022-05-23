#include "EngineMinimal.h"
#include "SpriteComponent.h"

namespace Engine
{
	namespace Level
	{
		SpriteComponent::SpriteComponent()
			:Visible(false)		
		{
			m_spriteBatch.reset();
		}
		void SpriteComponent::Init()
		{
		}
		void SpriteComponent::Tick(float elasedTime)
		{
		}
		void SpriteComponent::Draw()
		{
			m_spriteBatch->Begin();
			//m_spriteBatch->Draw();
			m_spriteBatch->End();
		}
	}
}

