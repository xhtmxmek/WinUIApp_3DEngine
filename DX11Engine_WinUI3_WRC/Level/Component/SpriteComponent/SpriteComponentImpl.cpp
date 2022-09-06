#include "EngineMinimal.h"
#include "SpriteComponentImpl.h"
#include "Common/DeviceResources.h"
#include "Common/EngineHelper.h"

namespace Engine
{
	namespace Component
	{
		SpriteComponentImpl::SpriteComponentImpl(const std::string& name)
			:ScreenPos(0.f, 0.f),
			TintColor(0.f, 0.f, 0.f, 0.f)
		{
			Load(L"");
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
			m_spriteBatch->Begin();			
			//Sprite가 필요한것.
			//screenPos, originpos, color, rotation			
			m_spriteBatch->Draw( m_texture.get(), ScreenPos, nullptr,
				TintColor, 0.f, Vector2(0.f,0.f) );

			m_spriteBatch->End();
		}

		void SpriteComponentImpl::Load(const winrt::hstring& textureName)
		{
			auto device = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDevice();
			winrt::hstring path;
			path = L"D:\\StudyDir\\WinUIApp_3DEngine\\TestProject\\Assets\\cat.png";
			wil::com_ptr_nothrow<ID3D11Resource> resource;
			HRESULT hr = DirectX::CreateWICTextureFromFile(device, path.c_str(),
				//CreateWICTextureFromFile(device, L"Assets/cat.png",
				resource.addressof(),
				m_texture.put());

			//com_ptr_nothrow<ID3D11Texture2D> cat;
			//DX::ThrowIfFailed(resource.query_to(cat.addressof()));

			//CD3D11_TEXTURE2D_DESC catDesc;
			//cat->GetDesc(&catDesc);
		}


	}
}

