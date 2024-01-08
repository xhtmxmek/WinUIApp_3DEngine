#include "pch.h"
#include "EngineAsset/Material.h"
#include "MaterialDrawer.h"
#include "Renderer/Resource/DeviceResources.h"
#include "Renderer/Resource/RenderStateObjectManager.h"

namespace Engine
{
	using namespace EngineAsset;

	namespace Renderer
	{
		void MaterialDrawer::DrawMaterial(const weak_ptr<EngineAsset::Material>& material)
		{
			//Todo : instanced material 구분

			auto d3dContext = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();


			//renderState setting
			/*
			* unreal은 BasePass는 BassPass 전용 렌더스테이트를, transparent는 반투명 렌더스테이트를 가져와서 사용했다.
			나도 그렇게 하자.
			override 하는걸로.
			*/
			if (material.expired())
				return;

			auto materialPtr = material.lock();
			if (!materialPtr)
				return;


			//auto RasterizerState = GraphicsLibrary::GetRasterizerState(GraphicsLibrary::RasterizerFillMode::Solid, GraphicsLibrary::RasterizerCullMode::Back);
			auto stateManager = GraphicsLibrary::RenderStateObjectManger::GetInstance();
			//stateManager.GetBlendState(materialPtr->GetBlendable())
			DX::DeviceResourcesUtil::GetDeviceResources()->SetRenderState();

			/*
			* 셰이더 상수버퍼는 추후에 매크로로 바이트 배열 만들어서 셰이더에 넘기기. 지금은 그냥 구조체로 하기.
			*/
			materialPtr->GetAmbientColor();

			//vertexShader Output
			for (UINT i = 0; i < TextureKey::Texture_Max; i++)
			{
				//d3dContext->PSSetShaderResources(i, 1, textures_[i]->GetShaderResourceView().addressof());
			}
		}
	}
}