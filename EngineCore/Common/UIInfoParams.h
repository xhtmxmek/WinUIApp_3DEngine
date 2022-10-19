#pragma once

namespace Engine
{
	struct SwapchainPanelInfo
	{
		bool IsLoaded;
		Type::Vector2f CompositionScale;
		Type::Size ActureSize;
		double RasterizationScale;
		std::function<void(IDXGISwapChain3*)> RegisterSwapChainToUIPanelCallBack;

	};
}