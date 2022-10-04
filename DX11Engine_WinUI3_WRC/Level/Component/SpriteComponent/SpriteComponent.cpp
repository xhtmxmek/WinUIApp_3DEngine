#include "EngineMinimal.h"
#include "SpriteComponent.h"
#include "Common/DeviceResources.h"
#include "EngineAsset/Texture.h"

namespace Engine
{
	namespace Component
	{
		RUNTIME_CLASS_IMPL(SpriteComponent)

		SpriteComponent::SpriteComponent(const std::string& name)
			:DrawableComponent(name)			
		{
			auto deviceContext = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
			SpriteBatch = make_unique<DirectX::SpriteBatch>(deviceContext);
			//BasicTexture = EngineAsset::TextureManager::GetInstance().GetTexture(L"D:\\StudyDir\\WinUIApp_3DEngine\\TestProject\\Assets\\cat.png");
			//const std::shared_ptr<EngineAsset::Texture> hello;
			//const std::shared_ptr<EngineAsset::Texture>& test = hello;
			BasicTexture = EngineAsset::TextureManager::GetInstance().GetTexture(L"Textures\\cat.png");
			protoType.Test();
		}		

		void SpriteComponent::Init()
		{			
		}

		void SpriteComponent::Tick(float elasedTime)
		{		
		}

		void SpriteComponent::Draw()
		{
			SpriteBatch->Begin();
			////Sprite가 필요한것.
			////screenPos, originpos, color, rotation			
			//ScreenPos = Vector2(200.0f, 200.0f);
			//SpriteBatch->Draw(BasicTexture->GetShaderResourceView().get(), ScreenPos, nullptr,
			//	TintColor, Rotation, Vector2(200.f, 200.f));

			SpriteBatch->End();
		}
	}
}

