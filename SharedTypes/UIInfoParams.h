#pragma once

namespace SharedTypes
{
	struct SwapchainPanelInfo
	{
		SwapchainPanelInfo() = default;
		SwapchainPanelInfo(const SwapchainPanelInfo&) = default;
		~SwapchainPanelInfo() = default;		
		//ENGINE_API 

		bool IsLoaded;
		Vector2f CompositionScale;
		Size ActureSize;
		double RasterizationScale;		
	};
}