#pragma once

namespace Engine
{
	namespace Renderer
	{
		class MeshDrawer;
	}
	namespace Asset
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
		class Mesh
		{
		public:
			Mesh();
			~Mesh();

			/*
			* mesh를 로드하면 aiScene에 기본적인 메시 정보들이 들어가 있다. submesh부터 vertex와 index, material, texture등 갖가지 정보 다 들어있음.
			* 1) aiScene을 들고 있고 이거에 맞춰서 리소스 클래스를 생성할 것인가? 이렇게 되면 머티리얼 매니저에서도 aiScene의 material을 참조, Mesh Table에서도 aiScene의 Mesh를 참조. 
			* 여러가지 리소스 매니저가 aiScene의 서브 리소스를  참조해야 됨. 이런 형태를 가져가고 싶지는 않음.
			* 2)자체 리소스 포맷을 어차피 만들거임. Mesh든 texture든. 그렇다면 scene을 자체 리소스 포맷에 맞게 한번더 정리하면됨. 이렇게 되면 리소스를 두번 읽어들이는 형태가 되기 때문에
			* 로딩 성능면에서는 떨어질지라도 관리와 코딩 측면에서는 더 유리함.
			*/

			bool Load(const string& fileName);
			void DrawNode();
			void DrawNodeInternal(aiNode* piNode, const aiMatrix4x4& piMatrix);
			void Unload();
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