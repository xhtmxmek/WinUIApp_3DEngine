#include "pch.h"
#include "Path.h"

namespace Engine
{	
	std::wstring Path::EngineDir;
	std::wstring Path::ProjectDir;
	std::wstring Path::ProjectName;

	void Path::InitBasePathes()
	{		
		//EngineDir = winrt::Windows::ApplicationModel::Package::Current().InstalledLocation().Path();
		//추후 옵션파일에서 로드하는걸로 바꿔주기
		ProjectDir = L"D:\\StudyDir\\WinUI_3DEngine\\TestProject";
		//ProjectDir = L"D:\\DX11Engine\\TestProject";
		ProjectName = L"TestProject.DLL";
	}
}