#pragma once

namespace Engine
{
	struct SwapchainPanelInfo
	{
		bool Loaded;
		Type::Vector2f CompositionScale;
		Type::Size ActureSize;
		float RasterizationScale;
		std::function<void(IDXGISwapChain3*)> RegisterSwapChainToUIPanelCallBack;

	};
}