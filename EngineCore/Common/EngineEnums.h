#pragma once

namespace Engine
{
	enum class DisplayOrientation
	{
		None = 0,
		Landscape = 0x1,
		Portrait = 0x2,
		LandscapeFlipped = 0x4,
		PortraitFlipped = 0x8,
	};	
}