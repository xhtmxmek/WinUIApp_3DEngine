#include "EngineMinimal.h"
#include "Path.h"

namespace Engine
{		
	winrt::hstring Path::ApplicationDir;
	winrt::hstring Path::ProjectDir;

	void Path::InitBasePathes()
	{
		ApplicationDir = winrt::Windows::ApplicationModel::Package::Current().InstalledLocation().Path();
		//추후 옵션파일에서 로드하는걸로 바꿔주기
		ProjectDir = L"D:\\StudyDir\\WinUIApp_3DEngine\\TestProject";
	}
}