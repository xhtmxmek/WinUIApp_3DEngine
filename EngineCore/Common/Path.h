#pragma once
namespace Engine
{
	class Path
	{
	public:		
		//static winrt::hstring ApplicationDir;
		//static winrt::hstring ProjectDir;
		static std::wstring EngineDir;
		static std::wstring ProjectDir;
		static std::wstring ProjectName;
		static void InitBasePathes();					
	};
}
