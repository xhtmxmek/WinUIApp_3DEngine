#pragma once

namespace Engine
{
	namespace Renderer
	{
		namespace RHI
		{
#pragma region Initialize
			void InitRenderResources();
			void InitPipelineStateObject();
#pragma endregion

#pragma region Pause/Relase
			void ClearRenderResources();			
			void ReleaseRenderResources();
#pragma endregion

#pragma RenderStateObject
			std::weak_ptr<RHIDepthStencilState> CreateRHIDepthStencilState();
#pragma endregion			
		}
	}
}