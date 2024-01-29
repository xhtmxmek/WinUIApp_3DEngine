#include "pch.h"
#include "EngineAsset/Material.h"
#include "MaterialDrawer.h"
#include "Resource/DeviceResources.h"
#include "Resource/RenderStateObjectManager.h"
#include "Resource/ConstantBuffer.h"
#include "Shader/ShaderObjectManager.h"
#include "Shader/ShaderObject.h"
#include "EngineAsset/Texture.h"

namespace Engine
{
	using namespace EngineAsset;

	namespace Renderer
	{
		using namespace GraphicsLibrary;

		void MaterialDrawer::DrawMaterial(const weak_ptr<EngineAsset::Material>& material)
		{
			//Todo : instanced material 구분
			//Todo : 패스 구분하여 override하기 (basepass, 반투명 pass)

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
			auto uniformBuffer = LockMaterialUniformBuffer();
		
			uniformBuffer->DiffuseColor = materialPtr->GetDiffuseColor();
			uniformBuffer->AmbientColor = materialPtr->GetAmbientColor();
			uniformBuffer->SpecularColor = materialPtr->GetSpecularColor();

			UnLockMaterialUniformBuffer();

			//shdaer set. Todo : pass마다 달라진다. materialParam으로 Lit혹은 unlit 혹은? 어떤거 넣을지 안정해짐. 일단 lit으로 고정.
			//lit으로 하려면 override 만들어야함.
			//drawShader_ = ShaderObjectManager::GetInstance().GetShader(ShaderType::Lit);
			drawShader_->SetShaderOnPipeline();
			
			
			//vertexShader Output
			for (UINT i = 0; i < TextureKey::Texture_Max; i++)
			{
				auto texture = materialPtr->GetTexture(static_cast<EngineAsset::TextureKey>(i));
				if (texture.has_value())
				{
					auto texturePtr = texture.value().lock();
					if (texturePtr)
						d3dContext->PSSetShaderResources(i, 1, texturePtr->GetShaderResourceView().addressof());
				}				
			}
		}
	}
}