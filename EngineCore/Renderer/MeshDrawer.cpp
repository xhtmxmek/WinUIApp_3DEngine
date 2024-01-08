#include "pch.h"
#include "MeshDrawer.h"
#include "Renderer/Resource/DeviceResources.h"
#include "Renderer/Resource/GraphicsLibraryResource.h"
#include "EngineAsset/Material.h"
#include "Renderer/MaterialDrawer.h"

namespace Engine
{
	namespace Renderer
	{
		void MeshDrawer::SetupMesh(aiMesh* srcMesh)
		{
			if (!srcMesh)
				return;

			vertices_.reserve(srcMesh->mNumVertices);
			vertices_.resize(srcMesh->mNumVertices);

			for (UINT i = 0; i < srcMesh->mNumVertices; i++)
			{
				VERTEX vertex;
				vertices_[i].Position = srcMesh->mVertices[i];

				if (srcMesh->mTextureCoords[0]) {
					vertices_[i].texcoord = srcMesh->mTextureCoords[0][i];
				}

				if (srcMesh->HasNormals())
				{
					vertices_[i].Normal = srcMesh->mNormals[i];
				}

				if (srcMesh->HasTangentsAndBitangents())
				{

				}

				if (srcMesh->HasVertexColors(0))
				{

				}
			}

			if (srcMesh->HasFaces())
			{
				//face�� 3�� �ƴ� ��쵵 �ְ����� �ϴ� 3�� ��츦 �⺻���� �Ѵ�.
				//3���� Ŭ��� ���� �α�.
				indices_.reserve(srcMesh->mNumFaces * 3);
				indices_.resize(srcMesh->mNumFaces * 3);
				for (unsigned int i = 0; i < srcMesh->mNumFaces; i++)
				{
					for (unsigned int index = 0; srcMesh->mFaces[i].mNumIndices; index++)
					{
						indices_[i * 3 + index] = srcMesh->mFaces[i].mIndices[index];
					}
				}
			}

			if (srcMesh->HasBones())
			{
				for (unsigned int i = 0; i < srcMesh->mNumBones; i++)
				{
					for (unsigned int j = 0; j < srcMesh->mBones[i]->mNumWeights; j++)
					{
						//vertex�� bone�� ���Խ�Ű�� ����� bone�� Weight�� ���� ���ۿ� ��� ����� �ִ�.
						//bone�� index�� weight�� vertex�� ��´�.
						float boneWeight = (float)srcMesh->mBones[i]->mWeights[j].mWeight;
						unsigned int vertexID = srcMesh->mBones[i]->mWeights[j].mVertexId;

						for (unsigned int k = 0; k < Num_Bone_PerVertex; k++)
						{
							if (vertices_[vertexID].BoneWeights[k] == 0)
							{
								vertices_[vertexID].BoneIDs[k] = i;
								vertices_[vertexID].BoneWeights[k] = boneWeight;
							}
							break;
						}
					}
				}
			}

			UINT vertexSize = sizeof(VERTEX);
			Renderer::GraphicsLibrary::CreateBufferFromData(&VertexBuffer_, D3D11_BIND_VERTEX_BUFFER, vertices_.data(), vertexSize * (UINT)vertices_.size(),
				D3D11_USAGE_DEFAULT, 0);
			Renderer::GraphicsLibrary::CreateBufferFromData(&VertexBuffer_, D3D11_BIND_INDEX_BUFFER, indices_.data(), sizeof(UINT) * (UINT)indices_.size(),
				D3D11_USAGE_DEFAULT, 0);
		}

		void MeshDrawer::DrawIndexed()
		{
			//���� ������ �϶��� ���ķ������� �ƴҶ��� ���еǾ�� �Ѵ�.
			/*
			* ���� ������ �ϋ� : ûũ ������ �ɰ��� finishCommandList�� ��� ��ϸ����.
			* ������ �Ҷ� ��Ƽ���� ���� �������ϵ�, �ش� �н����� ����� �ɰ���.
			* �θ� ��Ƽ������ �ѹ��� ������Ʈ �ȴ�. ��Ƽ���� �ν��Ͻ��� �ν��Ͻ� ���� ������Ʈ �ȴ�. �̰� �����̵� �ƴϵ� ������.
			*/

			//�н����� ����������Ʈ�� �ٸ��� ��Ƽ���󸶴� ����������Ʈ�� �ٸ���.
			//��Ƽ������ �ʱⰪ Ȥ�� ������Ƽ�� ������Ʈ�ɶ� ����������Ʈ�� �ٲ��.
			
			//parent Material�� �н��� �ѹ��� ������. material instance�� �޽ô� ������
			MaterialDrawer::DrawMaterial(material_);

			UINT stride = sizeof(VERTEX);
			UINT offset = 0;

			auto context = DX::DeviceResourcesUtil::GetDeviceResources()->GetD3DDeviceContext();
			context->IASetVertexBuffers(0, 1, &VertexBuffer_, &stride, &offset);
			context->IASetIndexBuffer(IndexBuffer_, DXGI_FORMAT_R16_UINT, 0);
			//context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST);
			context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			context->DrawIndexed(indices_.size(), 0, 0);

		}
	}
}

