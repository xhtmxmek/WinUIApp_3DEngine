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
		* asset�� animation�� ������ ���� �� ����.
		* ������ �������� ���� �ִϸ��̼ǿ� ���� ���� �ִϸ��̼� ���� ����.
		* �׷��� �׷� ��� ¥�⿡�� �ʹ� �����ɸ�. �׳� �ּº��� �ε��ϴ°ɷ�.
		* ���� ������ �ִϸ��̼��̶� �޽� ���δ� ����Ʈ�ϴ� ����. ������ ���������� �ε��Ҽ��־���ϴµ�
		* �׷� ��� �����ϱ⿡�� ü���̾ȵ�
		* aiMesh�� aiMaterial�� �״�� ����Ҽ��� ����. Mesh�� dx/opengl ���ҽ��� �����ؾ���
		* material ���� ��������. aiMesh�� �����ͷ� ������ �ְų� 
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