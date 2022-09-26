#include "EngineMinimal.h"
#include "Texture.h"
#include "Common/DeviceResources.h"

namespace Engine
{
	namespace EngineAsset
	{
		bool Texture::Load(const wstring& textureName)
		{
			auto device = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDevice();
			winrt::hstring path;
			//path = L"D:\\StudyDir\\WinUIApp_3DEngine\\TestProject\\Assets\\cat.png";
			path = textureName;
			wil::com_ptr_nothrow<ID3D11Resource> resource;
			HRESULT hr = DirectX::CreateWICTextureFromFile(device, path.c_str(),
				//CreateWICTextureFromFile(device, L"Assets/cat.png",
				resource.addressof(),
				ShaderResourceView.put());

			return SUCCEEDED(hr);
		}
	}
}