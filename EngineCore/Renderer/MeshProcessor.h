#pragma once

namespace Engine
{
	namespace EngineAsset
	{
		class Material;
	}
	namespace Renderer
	{
		namespace RHI
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
			RHI::VertexInput VertexStream;
			RHI::Buffer IndexBuffer;
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

		//MeshDrawCommand를 생성하는 역할. 머티리얼과 메시 정보를 바탕으로 커맨드 생성. 메시 프로세서는 프리미티브가 추가될때마다 매번 동적으로 생성, 삭제. 캐싱됨.
		class MeshProcessor
		{
		private:
			MeshPass passType;
		public:
			void BuildMeshDrawCommand();
			//const FScene* RESTRICT Scene;
			//ERHIFeatureLevel::Type FeatureLevel;
			//const FSceneView* ViewIfDynamicMeshCommand;			
			//FMeshPassDrawListContext* DrawListContext;
		};

		class BasePassMeshProcessor
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