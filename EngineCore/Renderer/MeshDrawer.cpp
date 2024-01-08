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
				//face가 3이 아닌 경우도 있겠지만 일단 3인 경우를 기본으로 한다.
				//3보다 클경우 에러 로그.
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
						//vertex에 bone을 포함시키는 방법과 bone과 Weight를 따로 버퍼에 담는 방법이 있다.
						//bone의 index와 weight를 vertex에 담는다.
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
			//병렬 렌더링 일때와 병렬렌더링이 아닐때가 구분되어야 한다.
			/*
			* 병렬 렌더링 일떄 : 청크 단위로 쪼개서 finishCommandList로 명령 목록만든다.
			* 렌더링 할때 머티리얼 별로 렌더링하되, 해당 패스에서 명령을 쪼갠다.
			* 부모 머티리얼은 한번만 업데이트 된다. 머티리얼 인스턴스는 인스턴스 별로 업데이트 된다. 이건 병렬이든 아니든 무조건.
			*/

			//패스마다 렌더스테이트가 다르고 머티리얼마다 렌더스테이트가 다르다.
			//머티리얼은 초기값 혹은 프로퍼티가 업데이트될때 렌더스테이트가 바뀐다.
			
			//parent Material은 패스당 한번만 렌더링. material instance는 메시당 렌더링
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

