#pragma once

namespace Engine
{
    namespace EngineAsset
    {
        class Material;
    }
    namespace Renderer
    {
        namespace RLI
        {
            class VertexInput;
            class Buffer;
        }
        
        struct MeshDrawShaderBindings
        {
            //상수버퍼와 리소스 바인딩. 어떻게?
        };
        struct MeshDrawCommand
        {
            RLI::VertexInput VertexStream;
            RLI::Buffer IndexBuffer;
            MeshDrawShaderBindings ShaderBindings;

            unsigned int cached_pipeline_id;
            unsigned int first_index;
            unsigned int num_primitives;
            unsigned int num_instances;
            //IndirectArgs
        };

        const int Num_Bone_PerVertex = 4;

        class Material;
        struct VERTEX {
            Vector3f Position;
            Vector3f texcoord;
            Vector3f Normal;
            int BoneIDs[4];
            float BoneWeights[4];
        };

        //MeshDrawCommand를 생성하는 역할. 머티리얼과 메시 정보를 바탕으로 커맨드 생성.
        class MeshProcessor
        {

        };

        namespace DrawUtil
        {
            void SubmitDrawCommandToPipeline(const shared_ptr<MeshDrawCommand>& command);
            void SetGraphicsPipelineState();
            void SubmitCommand();
        }        
    }
}