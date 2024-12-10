#pragma once

namespace Engine
{
	namespace Asset
	{
		class Material;
	}
	namespace Renderer
	{
		namespace 
		namespace RHI
		{
			class VertexInput;
			class Buffer;
		}

		struct MeshDrawShaderBindings
		{			
			//ConstantBuffer			
			//상수버퍼
			//셰이더

		};

		//MeshInfo로부터 정해진 최종 렌더링될 Primitive의 형태
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


		//Primitive가 들고 있는 렌더링을 위한 모든 정보
		struct MeshInfo
		{			
			//MaterialInfo
			//LOD
			//WireFrame
			//Dithered
			//VertexInput(VertexLayOut, VertexBuffer)
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
			void BuildMeshDrawCommand(const MeshInfo& Info);
			//const FScene* RESTRICT Scene;
			//ERHIFeatureLevel::Type FeatureLevel;
			//const FSceneView* ViewIfDynamicMeshCommand;			
			//FMeshPassDrawListContext* DrawListContext;
		};

		class BasePassMeshProcessor
		{
			//BasePass에 사용할 Shader는 정해져 있음. 이 셰이더가 템플릿인가? 퍼뮤테이션에 따라 Skinned와 아닌것으로 나뉨/
			//BasePassShader<skinned>* shader;
			//BasePassRenderState<skinned>
			//ConstantBuffer<BasePass<skinned>>
		};

		namespace DrawUtil
		{
			void SubmitDrawCommandToPipeline(const shared_ptr<MeshDrawCommand>& command);
			void SetGraphicsPipelineState();
			void SubmitCommand();
		}
	}
}