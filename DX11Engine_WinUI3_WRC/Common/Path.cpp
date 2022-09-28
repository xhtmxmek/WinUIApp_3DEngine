#include "EngineMinimal.h"
#include "Path.h"

namespace Engine
{		
	winrt::hstring Path::ApplicationDir;
	winrt::hstring Path::ProjectDir;

	void Path::InitBasePathes()
	{
		ApplicationDir = winrt::Windows::ApplicationModel::Package::Current().InstalledLocation().Path();
		//���� �ɼ����Ͽ��� �ε��ϴ°ɷ� �ٲ��ֱ�
		ProjectDir = L"D:\\StudyDir\\WinUIApp_3DEngine\\TestProject";
	}
}