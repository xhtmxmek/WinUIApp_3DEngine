#include "pch.h"
#include "Material.h"
#include "Common/DeviceResources.h"

namespace Engine
{
	namespace EngineAsset
	{
		void Material::UpdateConstBuffers()
		{
		}

		void Material::DrawMaterial()
		{
			auto d3dContext = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
			d3dContext->PSSetShaderResources(DiffuseMapSlot, 1, DiffuseMap.put());
			d3dContext->PSSetShaderResources(NormalMapSlot, 1, NormalMap.put());
			d3dContext->PSSetShaderResources(SpecularMapSlot, 1, SpecularMap.put());
		}
	}
}
