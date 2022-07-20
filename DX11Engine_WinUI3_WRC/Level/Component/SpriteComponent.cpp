#include "EngineMinimal.h"
#include "SpriteComponent.h"
#include "SpriteComponentImpl.h"

namespace Engine
{
	namespace Component
	{
		RUNTIME_CLASS_IMPL(SpriteComponent)

		SpriteComponent::SpriteComponent(const std::string& name)
			:DrawableComponent(name),
			pImpl(nullptr)
		{
			pImpl = new SpriteComponentImpl(name);			
		}

		SpriteComponent::~SpriteComponent()
		{
			delete pImpl;
		}

		void SpriteComponent::Init()
		{
		}

		void SpriteComponent::Tick(float elasedTime)
		{
		}

		void SpriteComponent::Draw()
		{
			pImpl->Draw();			
		}
	}
}

