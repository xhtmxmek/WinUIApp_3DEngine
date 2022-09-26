#include "EngineMinimal.h"
//#include "Common/pImplClassDefine.h"
#include "SpriteComponentImpl.h"
#include "Common/DeviceResources.h"
#include "Common/EngineHelper.h"
#include "EngineAsset/Texture.h"

namespace Engine
{
	namespace Component
	{
		SpriteComponentImpl::SpriteComponentImpl(const std::string& name)
			:ScreenPos(0.f, 0.f),
			TintColor(0.f, 0.f, 0.f, 0.f)
		{
			SpriteBatch = make_unique<DirectX::SpriteBatch>();
			BasicTexture = EngineAsset::TextureManager::GetInstance().GetTexture(L"D:\\StudyDir\\WinUIApp_3DEngine\\TestProject\\Assets\\cat.png");
			//SpriteBatch->
			//Load(L"");
		}

		void SpriteComponentImpl::Init()
		{
			//m_spriteBatch
		}

		void SpriteComponentImpl::Tick(float elasedTime)
		{

		}

		void SpriteComponentImpl::Draw()
		{
			SpriteBatch->Begin();
			//Sprite가 필요한것.
			//screenPos, originpos, color, rotation			
			SpriteBatch->Draw(BasicTexture->GetShaderResourceView().get(), ScreenPos, nullptr,
				TintColor, Rotation, Vector2(0.f,0.f) );

			SpriteBatch->End();
		}

		void SpriteComponentImpl::Load(const winrt::hstring& textureName)
		{
			//if( BasicTexture )
			//	BasicTextu
			//com_ptr_nothrow<ID3D11Texture2D> cat;
			//DX::ThrowIfFailed(resource.query_to(cat.addressof()));

			//CD3D11_TEXTURE2D_DESC catDesc;
			//cat->GetDesc(&catDesc);
		}


	}
}

