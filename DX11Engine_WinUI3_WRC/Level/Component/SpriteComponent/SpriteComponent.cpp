#include "EngineMinimal.h"
#include "SpriteComponent.h"
#include "SpriteComponentImpl.h"
#include "Common/DeviceResources.h"

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
			pImpl->Tick(elasedTime);
		}

		void SpriteComponent::Draw()
		{
			pImpl->Draw();			
		}
		void SpriteComponent::Load(const winrt::hstring& textureName)
		{
			pImpl->Load(textureName);
		}
		void SpriteComponent::SetPosition(Vector2 screenPos)
		{
			pImpl->SetPosition(screenPos);
		}
	}
}

