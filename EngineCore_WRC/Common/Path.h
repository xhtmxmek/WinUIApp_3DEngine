#pragma once
namespace Engine
{
	class Path
	{
	public:		
		//static winrt::hstring ApplicationDir;
		//static winrt::hstring ProjectDir;
		static std::wstring ApplicationDir;
		static std::wstring ProjectDir;
		static void InitBasePathes();					
	};
}
