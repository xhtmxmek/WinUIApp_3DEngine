#pragma once

namespace Engine
{
	namespace Renderer
	{
		class MeshDrawer;
	}
	namespace EngineAsset
	{
		class Texture;

		/*
		* asset이 animation을 가지고 있을 수 있음.
		* 동일한 본구조를 가진 애니메이션에 대해 여러 애니메이션 매핑 가능.
		* 그러나 그런 기능 짜기에는 너무 오래걸림. 그냥 애셋별로 로드하는걸로.
		* 지금 구조는 애니메이션이랑 메쉬 전부다 임포트하는 구조. 원래는 선택적으로 로드할수있어야하는데
		* 그런 기능 구현하기에는 체력이안됨
		* aiMesh와 aiMaterial을 그대로 사용할수는 없음. Mesh는 dx/opengl 리소스를 포함해야함
		* material 역시 마찬가지. aiMesh를 포인터로 가지고 있거나 
		*/
		class ModelAsset
		{
		public:
			ModelAsset();
			~ModelAsset();

			bool Load(const string& fileName);
			void DrawNode();
			void DrawNodeInternal(aiNode* piNode, const aiMatrix4x4& piMatrix);
			void Close();
		private:
			void UpdateAnimByTime();
			void processNode(aiNode* node, const aiScene* scene);
			shared_ptr<Renderer::MeshDrawer> processMesh(aiMesh* mesh, const aiScene* scene);
			std::weak_ptr<Texture> LoadMaterialTexture(aiMaterial* mat, aiTextureType type, const aiScene* scene);
		private:
			aiScene* importedScene_;
			std::unique_ptr<AssimpView::SceneAnimator> animator_;

			std::string directory_;
			vector<std::shared_ptr<Renderer::MeshDrawer>> meshDrawers_;

		};
	}
}