#include "EngineMinimal.h"
#include "SpriteComponent.h"
#include "SpriteComponentImpl.h"
#include "Common/DeviceResources.h"

namespace Engine
{
	namespace Component
	{
		RUNTIME_CLASS_IMPL(SpriteComponent)
		//IMPL_CLASS_PROPERTY_DEFEINITION(SpriteComponent, Vector2, ScreenPos)
		//IMPL_CLASS_PROPERTY_DEFEINITION(SpriteComponent, shared_ptr<DirectX::SpriteBatch>, SpriteBatch)


		SpriteComponent::SpriteComponent(const std::string& name)
			:DrawableComponent(name),
			pImpl(nullptr)
		{
			pImpl = new SpriteComponentImpl(name);
			//SetDiffuseTexture()
		}

		SpriteComponent::~SpriteComponent()
		{
			delete pImpl;
		}

		void SpriteComponent::Init()
		{
			pImpl->Init();
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
	}
}

