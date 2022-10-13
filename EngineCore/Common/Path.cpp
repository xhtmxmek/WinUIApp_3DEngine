#include "pch.h"
#include "Path.h"

namespace Engine
{	
	std::wstring Path::ApplicationDir;
	std::wstring Path::ProjectDir;

	void Path::InitBasePathes()
	{		
		ApplicationDir = winrt::Windows::ApplicationModel::Package::Current().InstalledLocation().Path();
		//추후 옵션파일에서 로드하는걸로 바꿔주기
		ProjectDir = L"D:\\StudyDir\\WinUIApp_3DEngine\\TestProject";
	}
}