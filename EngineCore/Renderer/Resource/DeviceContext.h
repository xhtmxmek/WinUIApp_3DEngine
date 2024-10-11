#pragma once

namespace Engine
{
	namespace Renderer
	{
		namespace RHI
		{
#pragma region Initialize
			void InitRenderResources();
			void PostInitialize();
			void InitPipelineStateObject();
#pragma endregion

#pragma region Pause/Relase
			void ClearRenderResources();			
			void ReleaseRenderResources();
#pragma endregion

#pragma region RenderStateObject
			std::weak_ptr<RHIDepthStencilState> CreateRHIDepthStencilState();
#pragma endregion

#pragma region AppWindowTransform
			void ApplyWindowTransform(const WindowParam& param);
#pragma endregion
		}
	}
}