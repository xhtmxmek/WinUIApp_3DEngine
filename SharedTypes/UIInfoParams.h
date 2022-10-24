#pragma once

struct IDXGISwapChain3;

namespace SharedTypes
{
	struct SwapchainPanelInfo
	{				
		bool IsLoaded;
		Vector2f CompositionScale;
		Size ActureSize;
		double RasterizationScale;		
		std::function<void(IDXGISwapChain3*)> RegisterSwapChainToUIPanel;		
	};
}