#pragma once

/*
* Command는 VertexBuffer, IndexBuffer, Instanceing정보, RenderStateObject, Shader 정보를 가지고있다.
DX12의 경우에는 PSO 캐시 정보도 가지고 있다.
병렬렌더링일때는 해당 정보들을 쓰레드 & 디퍼드 컨텍스트로 쪼개서 RHICommand로 만듬.
일반 렌더링일때는 바로 파이프라인에 sumbmit.
*/

namespace Engine
{
	namespace Renderer
	{
		namespace RLI
		{
			class RLICommand
			{
				//Vertex			
			};
		}
	}
}
	