#include "pch.h"
#include "Material.h"
#include "Texture.h"
#include "Animation/SceneAnimator.h"
#include "Mesh.h"
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>

namespace Engine
{
	namespace Asset
	{
		Mesh::Mesh()
		{
		}

		Mesh::~Mesh()
		{
		}

		bool Mesh::Load(const string& fileName)
		{
			Assimp::Importer importer;

			const aiScene* importedScene_ = importer.ReadFile(fileName,
				aiProcess_Triangulate |
				aiProcess_ConvertToLeftHanded);

			if (!importedScene_)
				return false;

			meshDrawers_.reserve(importedScene_->mNumMeshes);
			meshDrawers_.resize(importedScene_->mNumMeshes);

			processNode(importedScene_->mRootNode, importedScene_);
			
			if (importedScene_->HasAnimations())
			{
				animator_ = make_unique<AssimpView::SceneAnimator>(importedScene_);
			}

			return false;
		}

		void Mesh::UpdateAnimByTime()
		{
			//anim update
//time을 어떻게 할것인가? 싱글톤을 만들어서 시간을 얻어와야할것 같다.
			static double lastPlaying = 0.;
			//g_dCurrent += clock() / double(CLOCKS_PER_SEC) - lastPlaying;

			//double time = g_dCurrent;
			double time = 0.0;
			aiAnimation* mAnim = animator_->CurrentAnim();
			if (mAnim && mAnim->mDuration > 0.0)
			{
				double tps = mAnim->mTicksPerSecond ? mAnim->mTicksPerSecond : 25.f;
				time = fmod(time, mAnim->mDuration / tps);
				//SendDlgItemMessage(g_hDlg, IDC_SLIDERANIM, TBM_SETPOS, TRUE, LPARAM(10000 * (time / (mAnim->mDuration / tps))));
			}

			animator_->Calculate(time);
			//lastPlaying = g_dCurrent;
		}

		void Mesh::DrawNode()
		{
			/*
			* primitiveComponent.Draw로 명령이 들어오면, 자신이 가지고 있는 Mesh을 draw한다.
			* 병렬 렌더링이 on일때와 off일때를 구분한다.(커맨드 리스트 만들기의 여부)
			* 
			*/

			UpdateAnimByTime();

			if (importedScene_->mRootNode != nullptr)
				DrawNodeInternal(importedScene_->mRootNode, importedScene_->mRootNode->mTransformation);
		}

		void Mesh::DrawNodeInternal(aiNode* piNode, const aiMatrix4x4& piMatrix)
		{
			aiMatrix4x4 aiMe = animator_->GetGlobalTransform(piNode);

			aiMe.Transpose();
			aiMe *= piMatrix;
			//WorldMatrix로 세팅

			for (unsigned int i = 0; i < piNode->mNumMeshes; ++i)
			{
				const aiMesh* mesh = importedScene_->mMeshes[piNode->mMeshes[i]];
				auto meshDrawer = meshDrawers_[piNode->mMeshes[i]];
				meshDrawer->DrawIndexed();
			}

			for (unsigned int i = 0; i < piNode->mNumChildren; ++i)
				DrawNodeInternal(piNode->mChildren[i], piMatrix);
		}

		void Mesh::processNode(aiNode* srcNode, const aiScene* scene)
		{
			for (UINT i = 0; i < srcNode->mNumMeshes; i++) {
				aiMesh* srcMesh = scene->mMeshes[srcNode->mMeshes[i]];
				meshDrawers_[srcNode->mMeshes[i]] = this->processMesh(srcMesh, scene);
			}

			for (UINT i = 0; i < srcNode->mNumChildren; i++) 
			{
				processNode(srcNode->mChildren[i], scene);
			}
		}

		shared_ptr<Renderer::MeshDrawer> Mesh::processMesh(aiMesh* srcMesh, const aiScene* scene)
		{
			auto out = make_shared<Renderer::MeshDrawer>();
			out->SetupMesh(srcMesh);

			if (scene->hasSkeletons())
			{
				//scene->mSkeletons
			}

			if (scene->HasMaterials())
			{
				auto srcMat = scene->mMaterials[srcMesh->mMaterialIndex];

				if (!srcMat)
				{					
					return nullptr;
				}
								
				auto newMaterial = MaterialManager::GetInstance().CreateMaterial(srcMat->GetName().C_Str());
				if (newMaterial.expired())
					return nullptr;
				
				auto matPtr = newMaterial.lock();

				Color4f parsedColor;
				if (srcMat->Get(AI_MATKEY_BLEND_FUNC, parsedColor) == AI_SUCCESS)
					matPtr->SetBaseColor(parsedColor);

				if (srcMat->Get(AI_MATKEY_COLOR_DIFFUSE, parsedColor) == AI_SUCCESS)
					matPtr->SetDiffuseColor(parsedColor);

				if (srcMat->Get(AI_MATKEY_COLOR_SPECULAR, parsedColor) == AI_SUCCESS)
					matPtr->SetSpecularColor(parsedColor);

				if (srcMat->Get(AI_MATKEY_COLOR_AMBIENT, parsedColor) == AI_SUCCESS)
					matPtr->SetAmbientColor(parsedColor);

				if (srcMat->Get(AI_MATKEY_COLOR_EMISSIVE, parsedColor) == AI_SUCCESS)
					matPtr->SetEmissiveColor(parsedColor);

				float parsedFactor;
				if (srcMat->Get(AI_MATKEY_OPACITY, parsedFactor) == AI_SUCCESS)
					matPtr->SetOpacity(parsedFactor);

				if (srcMat->Get(AI_MATKEY_BLEND_FUNC, parsedFactor) == AI_SUCCESS)
					matPtr->SetBlendable((bool)parsedFactor);

				if (srcMat->Get(AI_MATKEY_SPECULAR_FACTOR, parsedFactor) == AI_SUCCESS)
					matPtr->SetSpecularFactor(parsedFactor);

				if (srcMat->Get(AI_MATKEY_GLOSSINESS_FACTOR, parsedFactor) == AI_SUCCESS)
					matPtr->SetGlossinessFactor(parsedFactor);

				if (srcMat->Get(AI_MATKEY_SHININESS, parsedFactor) == AI_SUCCESS)
					matPtr->SetShinessFactor(parsedFactor);

				matPtr->SetTexture(TextureKey::DiffuseMap, LoadMaterialTexture(srcMat, aiTextureType_DIFFUSE, scene));
				matPtr->SetTexture(TextureKey::NormalMap, LoadMaterialTexture(srcMat, aiTextureType_NORMALS, scene));
				matPtr->SetTexture(TextureKey::SpecularMap, LoadMaterialTexture(srcMat, aiTextureType_SPECULAR, scene));
				matPtr->SetTexture(TextureKey::EmissiveMap, LoadMaterialTexture(srcMat, aiTextureType_EMISSIVE, scene));

				//pbr map
				matPtr->SetTexture(TextureKey::BaseColorMap, LoadMaterialTexture(srcMat, aiTextureType_BASE_COLOR, scene));
				matPtr->SetTexture(TextureKey::MetalicMap, LoadMaterialTexture(srcMat, aiTextureType_METALNESS, scene));
				matPtr->SetTexture(TextureKey::RoughnessMap, LoadMaterialTexture(srcMat, aiTextureType_DIFFUSE_ROUGHNESS, scene));



				out->material_ = newMaterial;
			}

			return out;
		}

		std::weak_ptr<Texture> Mesh::LoadMaterialTexture(aiMaterial* mat, aiTextureType type, const aiScene* scene)
		{
			aiString textureName;
			mat->GetTexture(type, 0, &textureName);
			std::string filename = std::string(textureName.C_Str());
			std::wstring filenameWstr = std::wstring(filename.begin(), filename.end());
			auto engineTexture = TextureManager::GetInstance().LoadTexture(filenameWstr);
			return engineTexture.value();
		}
	}
}