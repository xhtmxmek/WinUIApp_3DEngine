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
			//Todo : instanced material ����

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
			materialPtr->GetAmbientColor();

			//vertexShader Output
			for (UINT i = 0; i < TextureKey::Texture_Max; i++)
			{
				//d3dContext->PSSetShaderResources(i, 1, textures_[i]->GetShaderResourceView().addressof());
			}
		}
	}
}