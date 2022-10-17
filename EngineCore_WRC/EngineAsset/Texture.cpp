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
			���ҽ��� ���.
			1. ������ �������� ����
			2. ����� ������ Assets �������� ��.
			3. ��ŷ�ҋ��� Assets���� ���� ��Ű���� �ؾ��ҵ�.
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