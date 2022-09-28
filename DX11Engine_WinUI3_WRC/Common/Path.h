#pragma once
namespace Engine
{
	class Path
	{
	public:		
		static winrt::hstring ApplicationDir;
		static winrt::hstring ProjectDir;
		static void InitBasePathes();					
	};
}
