#include "EngineMinimal.h"
#include "Texture.h"
#include "Common/DeviceResources.h"

namespace Engine
{
	namespace EngineAsset
	{
		bool Texture::Load(const winrt::hstring& textureName)
		{
			auto device = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDevice();			
			/*
			리소스의 경로.
			1. 절대경로 지정으로 가능
			2. 상대경로 지정은 Assets 기준으로 됨.
			3. 패킹할떄는 Assets으로 복사 시키도록 해야할듯.
			*/						
			//path = L"Assets/Textures/cat.png";			
			wil::com_ptr_nothrow<ID3D11Resource> resource;
			HRESULT hr = DirectX::CreateWICTextureFromFile(device, textureName.c_str(),
				//CreateWICTextureFromFile(device, L"Assets/cat.png",
				resource.addressof(),
				ShaderResourceView.put());

			return SUCCEEDED(hr);
		}
	}
}