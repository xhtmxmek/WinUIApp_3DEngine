#include "pch.h"
#include "MeshProcessor.h"
#include "Renderer/Resource/DeviceResources.h"
#include "Renderer/Resource/RLIResource.h"
#include "EngineAsset/Material.h"
#include "Renderer/MaterialDrawer.h"

namespace Engine
{
	namespace Renderer
	{
		//void MeshDrawer::SetupMesh(aiMesh* srcMesh)
		//{
		//	if (!srcMesh)
		//		return;

		//	vertices_.reserve(srcMesh->mNumVertices);
		//	vertices_.resize(srcMesh->mNumVertices);

		//	for (UINT i = 0; i < srcMesh->mNumVertices; i++)
		//	{
		//		VERTEX vertex;
		//		vertices_[i].Position = srcMesh->mVertices[i];

		//		if (srcMesh->mTextureCoords[0]) {
		//			vertices_[i].texcoord = srcMesh->mTextureCoords[0][i];
		//		}

		//		if (srcMesh->HasNormals())
		//		{
		//			vertices_[i].Normal = srcMesh->mNormals[i];
		//		}

		//		if (srcMesh->HasTangentsAndBitangents())
		//		{

		//		}

		//		if (srcMesh->HasVertexColors(0))
		//		{

		//		}
		//	}

		//	if (srcMesh->HasFaces())
		//	{
		//		//face�� 3�� �ƴ� ��쵵 �ְ����� �ϴ� 3�� ��츦 �⺻���� �Ѵ�.
		//		//3���� Ŭ��� ���� �α�.
		//		indices_.reserve(srcMesh->mNumFaces * 3);
		//		indices_.resize(srcMesh->mNumFaces * 3);
		//		for (unsigned int i = 0; i < srcMesh->mNumFaces; i++)
		//		{
		//			for (unsigned int index = 0; srcMesh->mFaces[i].mNumIndices; index++)
		//			{
		//				indices_[i * 3 + index] = srcMesh->mFaces[i].mIndices[index];
		//			}
		//		}
		//	}

		//	if (srcMesh->HasBones())
		//	{
		//		for (unsigned int i = 0; i < srcMesh->mNumBones; i++)
		//		{
		//			for (unsigned int j = 0; j < srcMesh->mBones[i]->mNumWeights; j++)
		//			{
		//				//vertex�� bone�� ���Խ�Ű�� ����� bone�� Weight�� ���� ���ۿ� ��� ����� �ִ�.
		//				//bone�� index�� weight�� vertex�� ��´�.
		//				float boneWeight = (float)srcMesh->mBones[i]->mWeights[j].mWeight;
		//				unsigned int vertexID = srcMesh->mBones[i]->mWeights[j].mVertexId;

		//				for (unsigned int k = 0; k < Num_Bone_PerVertex; k++)
		//				{
		//					if (vertices_[vertexID].BoneWeights[k] == 0)
		//					{
		//						vertices_[vertexID].BoneIDs[k] = i;
		//						vertices_[vertexID].BoneWeights[k] = boneWeight;
		//					}
		//					break;
		//				}
		//			}
		//		}
		//	}

		//	UINT vertexSize = sizeof(VERTEX);
		//	Renderer::RLI::CreateBufferFromData(&VertexBuffer_, D3D11_BIND_VERTEX_BUFFER, vertices_.data(), vertexSize * (UINT)vertices_.size(),
		//		D3D11_USAGE_DEFAULT, 0);
		//	Renderer::RLI::CreateBufferFromData(&IndexBuffer_, D3D11_BIND_INDEX_BUFFER, indices_.data(), sizeof(UINT) * (UINT)indices_.size(),
		//		D3D11_USAGE_DEFAULT, 0);
		//}

		namespace DrawUtil
		{
			void SubmitDrawCommandToPipeline(const shared_ptr<MeshDrawCommand>& command)
			{
				SetGraphicsPipelineState();								
				SubmitCommand();
			}
			void SetGraphicsPipelineState()
			{

			//머티리얼 인스턴스도 고려해야함.
			/* 머티리얼 드로우어 로직
			* 
			* 	//			//Todo : instanced material ����
	////Todo : �н� �����Ͽ� override�ϱ� (basepass, ������ pass)

	//			auto d3dContext = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();


	//			//renderState setting
	//			/*
	//			* unreal�� BasePass�� BassPass ���� ����������Ʈ��, transparent�� ������ ����������Ʈ�� �����ͼ� ����ߴ�.
	//			���� �׷��� ����.
	//			override �ϴ°ɷ�.
	//			*/
	//			if (material.expired())
	//				return;

	//			auto materialPtr = material.lock();
	//			if (!materialPtr)
	//				return;


	//			//auto RasterizerState = RLI::GetRasterizerState(RLI::RasterizerFillMode::Solid, RLI::RasterizerCullMode::Back);
	//			auto stateManager = RLI::RenderStateObjectManger::GetInstance();
	//			//stateManager.GetBlendState(materialPtr->GetBlendable())
	//			DX::DeviceResourcesUtil::GetDeviceResources()->SetRenderState();

	//			/*
	//			* ���̴� ������۴� ���Ŀ� ��ũ�η� ����Ʈ �迭 ���� ���̴��� �ѱ��. ������ �׳� ����ü�� �ϱ�.
	//			*/
	//			auto uniformBuffer = LockMaterialUniformBuffer();

	//			uniformBuffer->DiffuseColor = materialPtr->GetDiffuseColor();
	//			uniformBuffer->AmbientColor = materialPtr->GetAmbientColor();
	//			uniformBuffer->SpecularColor = materialPtr->GetSpecularColor();

	//			UnLockMaterialUniformBuffer();

	//			//shdaer set. Todo : pass���� �޶�����. materialParam���� LitȤ�� unlit Ȥ��? ��� ������ ��������. �ϴ� lit���� ����.
	//			//lit���� �Ϸ��� override ��������.
	//			//drawShader_ = ShaderObjectManager::GetInstance().GetShader(ShaderType::Lit);
	//			drawShader_->SetShaderOnPipeline();


	//			//vertexShader Output
	//			for (UINT i = 0; i < TextureKey::Texture_Max; i++)
	//			{
	//				auto texture = materialPtr->GetTexture(static_cast<EngineAsset::TextureKey>(i));
	//				if (texture.has_value())
	//				{
	//					auto texturePtr = texture.value().lock();
	//					if (texturePtr)
	//						d3dContext->PSSetShaderResources(i, 1, texturePtr->GetShaderResourceView().addressof());
	//				}
	//			}
			
				//uniformBuffer
				//ShaderResource
				//Shader
				//PSO
				
				//	auto context = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
				//	context->IASetVertexBuffers(0, 1, &VertexBuffer_, &stride, &offset);
				//	context->IASetIndexBuffer(IndexBuffer_, DXGI_FORMAT_R16_UINT, 0);
				//	//context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);
				//	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			}
			void SubmitCommand()
			{
				//context->DrawIndexed(indices_.size(), 0, 0);
			}
		}
	}
}
