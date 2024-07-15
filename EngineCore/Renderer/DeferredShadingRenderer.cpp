#include "pch.h"
#include "DeferredShadingRenderer.h"
#include "Component/ComponentBase/ComponentBase.h"
#include "Scene.h"
#include "RendererBaseHeader.h"

namespace Engine
{
	namespace Renderer
	{		
		void DeferredShadingRenderer::Render()
		{
			//3D 액터 먼저그림(포워드, 디퍼드 모드 선택해서 그림)
			//렌더러에서 월드 세팅을 받아서 그림. 혹은 월드가 렌더러를 받아서 그림.
			//2D 액터는 어떻게 그리나? 어디소속인가. 일단 액터는 전부 월드 소속.
			//렌더러는 drawComponent list를 가지고 씬을 그린다.


			/*
			* ue에서 코드를 본것을 기준으로 따라해보자.
			* mesh렌더링은 각 패스 별로 meshProcessor가 있다.
			* meshProcessor는 primitive의 vertex, 각 pass의 shader, 각 pass별로 준비되어있는 renderstate등을
			* 조합한다.
			* 일반적으로 static mesh의 drawcommand는 캐싱 된다. dynamic mesh의 drawcommand는 매프레임 생성된다.
			* dynamic mesh는 skeletal mesh부터 시작해서,fog나 파티클 같은 것들이 해당된다.
			*
			*/

			ComputeVisibility();

			RenderShadowDepth();
			
			RenderBasePass();

			//deferred light, 반투명 볼륨 적용
			RenderLights();

			RenderTranslucencyPass();

			//RenderFog..particle.. etc...
			RenderVolumetricFog();

			//안쪽에서 translucency pass composit
			RenderPostProcessingPass();

			//for (auto& drawComponent : DrawList )
			//{
			//	if (drawComponent != nullptr)
			//		drawComponent->Draw();
			//}
		}

#pragma region Visibility Check
		void DeferredShadingRenderer::InitView()
		{
			ComputeVisibility();
			GatherDynamicMesh();

		}
		void DeferredShadingRenderer::ComputeVisibility()
		{
			//Scene이 가지고있는 primitive들의 visibility 검사

			/*
			* 1.frustomculling
			* 2.occlusionculling
			* 3.각 drawComponent의 visibility 검사
			* 4.쓰레드 이용하여 병렬로 검사
			* 5.모든 Primitive 검사하여,가시성 통과한 Primitive의 DrawCommand만 VisibieCommandList에 저장.
			* 6.위는 staticMesh에 대한 것이며, Scene의 dinamicMesh도 검사하여 여기서 매프레임 생성.
			* VisibleDrawCommand는 언리얼에선 View가 가지고 있음. 우리도 그냥 View라는 구조체 만들어서 들고있게 하자.
			*/
			OcclusionCull();
			FrustomCull();
		}
		void DeferredShadingRenderer::GatherDynamicMesh()
		{
			//Scene의 Dynamic Mesh의 drawCommand 생성
			//View의 visibleDrawCommand에 drawCommand 추가
			//visibleDrawCommand는 CachedDrawCommands와 그냥 Drawcommands의 조합이다.
			//visibleDrawCommand는 각 pass별로 있다.
		}
		void DeferredShadingRenderer::OcclusionCull()
		{
		}
		void DeferredShadingRenderer::FrustomCull()
		{
		}
#pragma endregion


		void DeferredShadingRenderer::RenderShadowDepth()
		{
		}
		void DeferredShadingRenderer::RenderBasePass()
		{
			/*VisibleDrawCommand를 Draw한다. 안쪽에서 병렬로 Draw한다.
			*StaticMesh는 렌더명령이 변하지 않는 한 캐싱해서 렌더명령을 쓴다
			* MeshProcessor가 staticMesh 생성시 버텍스, pass별 RenderState, pass별 Shader등을 조합하여 DrawCommand를 만든다.
			* DynamicMesh는 매프레임 MeshProcessor를 이용하여 렌더 명령을 만든다.
			*/

			SceneInfo->DispatchVisibleDrawCommandList(MeshPass::Base);			
		}
		void DeferredShadingRenderer::RenderLights()
		{
			//라이트는 로컬라이트, 디렉셔널 라이트, 에어리어라이트(렉트라이트?), 타일 등이있다.
			//글로벌일루미네이션은 학습 후에 적용해보기.
		}
		void DeferredShadingRenderer::RenderTranslucencyPass()
		{
			/*Todo
			* 반투명은 씬칼라 위에
			* pp의 여러위치에 삽입될수 있는 반투명 패스들이 있음.이건 추후 필요하면 넣기
			* 반투명 볼륨은아직 잘 모름. 스터디 필요.
			*/
		}
		void DeferredShadingRenderer::RenderVolumetricFog()
		{
			/*
			* volume 렌더링 공부 필요. 특히 fog
			*/
		}
		void DeferredShadingRenderer::RenderPostProcessingPass()
		{
			/*
			* UE에서 post process는 순서가 고정되어있음. 대부분은 컴퓨트 셰이더를 사용중임.
			*/
		}
	}
}

