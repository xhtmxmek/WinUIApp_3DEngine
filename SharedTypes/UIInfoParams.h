#pragma once

struct IDXGISwapChain;

namespace SharedTypes
{
	struct SwapchainPanelInfo
	{				
		bool IsLoaded;
		Vector2f CompositionScale;
		Size ActureSize;
		double RasterizationScale;		
		std::function<void(IDXGISwapChain*)> RegisterSwapChainToUIPanel;		
	};
}