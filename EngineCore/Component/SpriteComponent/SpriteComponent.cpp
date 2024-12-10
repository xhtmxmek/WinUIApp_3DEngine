#include "pch.h"
#include "SpriteComponent.h"
#include "Renderer/Resource/DeviceContext.h"
#include "EngineAsset/Texture.h"

namespace Engine
{
	namespace Component
	{
		RUNTIME_CLASS_IMPL(SpriteComponent)

		SpriteComponent::SpriteComponent(const std::string& name)
			:DrawableComponent(name)			
		{
			auto deviceContext = DeviceContextWrapper::GetDeviceContext()->GetD3DDeviceContext();
			SpriteBatch = make_unique<DirectX::SpriteBatch>(deviceContext);
			//BasicTexture = EngineAsset::TextureManager::GetInstance().GetTexture(L"D:\\StudyDir\\WinUIApp_3DEngine\\TestProject\\Assets\\cat.png");
			//const std::shared_ptr<EngineAsset::Texture> hello;
			//const std::shared_ptr<EngineAsset::Texture>& test = hello;
			//BasicTexture = EngineAsset::TextureManager::GetInstance().GetTexture(L"Textures\\cat.png");			
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
			////Sprite�� �ʿ��Ѱ�.
			////screenPos, originpos, color, rotation			
			//ScreenPos = Vector2(200.0f, 200.0f);
			//SpriteBatch->Draw(BasicTexture->GetShaderResourceView().get(), ScreenPos, nullptr,
			//	TintColor, Rotation, Vector2(200.f, 200.f));

			SpriteBatch->End();
		}
	}
}

