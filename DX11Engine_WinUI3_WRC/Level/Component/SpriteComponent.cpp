#include "EngineMinimal.h"
#include "SpriteComponent.h"

namespace Engine
{
	namespace Component
	{
		RUNTIME_CLASS_IMPL(SpriteComponent)

		SpriteComponent::SpriteComponent(const std::string& name)
			:DrawableComponent(name)
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

