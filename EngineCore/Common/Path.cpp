#include "pch.h"
#include "Path.h"

namespace Engine
{	
	std::wstring Path::EngineDir;
	std::wstring Path::ProjectDir;

	void Path::InitBasePathes()
	{		
		//EngineDir = winrt::Windows::ApplicationModel::Package::Current().InstalledLocation().Path();
		//���� �ɼ����Ͽ��� �ε��ϴ°ɷ� �ٲ��ֱ�
		ProjectDir = L"D:\\StudyDir\\WinUIApp_3DEngine\\TestProject";
	}
}