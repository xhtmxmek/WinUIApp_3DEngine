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
			//Todo : instanced material ����
			//Todo : �н� �����Ͽ� override�ϱ� (basepass, ������ pass)

			auto d3dContext = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();


			//renderState setting
			/*
			* unreal�� BasePass�� BassPass ���� ����������Ʈ��, transparent�� ������ ����������Ʈ�� �����ͼ� ����ߴ�.
			���� �׷��� ����.
			override �ϴ°ɷ�.
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
			* ���̴� ������۴� ���Ŀ� ��ũ�η� ����Ʈ �迭 ���� ���̴��� �ѱ��. ������ �׳� ����ü�� �ϱ�.
			*/
			auto uniformBuffer = LockMaterialUniformBuffer();
		
			uniformBuffer->DiffuseColor = materialPtr->GetDiffuseColor();
			uniformBuffer->AmbientColor = materialPtr->GetAmbientColor();
			uniformBuffer->SpecularColor = materialPtr->GetSpecularColor();

			UnLockMaterialUniformBuffer();

			//shdaer set. Todo : pass���� �޶�����. materialParam���� LitȤ�� unlit Ȥ��? ��� ������ ��������. �ϴ� lit���� ����.
			//lit���� �Ϸ��� override ��������.
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