#pragma once

namespace Engine
{
	struct SwapchainPanelInfo
	{
		ENGINE_API SwapchainPanelInfo() = default;
		ENGINE_API SwapchainPanelInfo(const SwapchainPanelInfo&) = default;
		ENGINE_API ~SwapchainPanelInfo() = default;		
		//ENGINE_API 

		bool IsLoaded;
		Type::Vector2f CompositionScale;
		Type::Size ActureSize;
		double RasterizationScale;
		std::function<void(IDXGISwapChain3*)> RegisterSwapChainToUIPanelCallBack;

	};
}