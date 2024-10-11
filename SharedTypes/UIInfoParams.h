#pragma once

struct IDXGISwapChain;

namespace SharedTypes
{
	struct WindowParam
	{				
		bool IsLoaded;
		Vector2f CompositionScale;
		Size ActureSize;
		double RasterizationScale;		
	};

	
	template<typename AppWindowType>
	using AppWindowRegisterFunc = std::function<void(AppWindowType*)>;

	template<typename AppWindowType>
	struct WindowInitParam
	{
		WindowParam _WindowParam;
		AppWindowRegisterFunc<AppWindowType> _registerFunc;
		AppWindowType* _windowHandle;

	};
}