#include "pch.h"
#include "SpriteComponent.h"

namespace Engine
{
	namespace Component
	{
		void SpriteComponent::Draw()
		{
			m_spriteBatch->Begin();
			//m_spriteBatch->Draw();
			m_spriteBatch->End();
		}
	}
}

