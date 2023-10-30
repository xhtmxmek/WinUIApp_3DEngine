#include "pch.h"
#include "Texture.h"
#include "Material.h"
#include "Renderer/Resource/DeviceResources.h"

namespace Engine
{
	namespace EngineAsset
	{
		Material::Material()
		{			
			textures_.reserve(TextureKey::Texture_Max);
			textures_.resize(TextureKey::Texture_Max, nullptr);
		}

		void Material::UpdateConstBuffers()
		{
		}

		void Material::DrawMaterial()
		{
			auto d3dContext = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
			
			for (UINT i = 0; i < TextureKey::Texture_Max; i++)
			{
				d3dContext->PSSetShaderResources(i, 1, textures_[i]->GetShaderResourceView().addressof());
			}
		}
	}
}
