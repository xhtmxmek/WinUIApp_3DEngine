#pragma once

namespace Engine
{
	namespace Renderer
	{
		namespace RHI
		{
			struct DepthStencilDesc;

#pragma region Initialize
			void InitRenderResources();
			void PostInitialize();
			//void InitPipelineStateObject();
#pragma endregion

#pragma region Pause/Relase
			void ClearRenderResources();			
			void ReleaseRenderResources();
#pragma endregion

#pragma region RenderStateObject
			std::shared_ptr<RHIDepthStencilState> CreateRHIDepthStencilState(const DepthStencilDesc& Desc);
#pragma endregion

#pragma region AppWindowTransform
			void ApplyWindowTransform(const WindowParam& param);
#pragma endregion
		}
	}
}