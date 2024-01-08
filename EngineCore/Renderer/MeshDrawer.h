#pragma once

namespace Engine
{
    namespace EngineAsset
    {
        class Material;
    }
    namespace Renderer
    {
        const int Num_Bone_PerVertex = 4;

        class Material;
        struct VERTEX {
            Vector3f Position;
            Vector3f texcoord;
            Vector3f Normal;
            int BoneIDs[4];
            float BoneWeights[4];
        };

        class MeshDrawer {
        public:
            std::vector<VERTEX> vertices_;
            std::vector<UINT> indices_;
            weak_ptr<EngineAsset::Material> material_;
            ID3D11Buffer* VertexBuffer_;
            ID3D11Buffer* IndexBuffer_;

            //Mesh(const std::vector<VERTEX>& vertices, const std::vector<UINT>& indices, const std::vector<shared_ptr<Material>>& materials) :
            //    vertices_(vertices),
            //    indices_(indices),
            //    materials_(materials),
            //    VertexBuffer_(nullptr),
            //    IndexBuffer_(nullptr) {
            //    //this->setupMesh(this->dev_);
            //}
        public:
            void SetupMesh(aiMesh* srcMesh);
            void DrawIndexed();
        };
    }
}