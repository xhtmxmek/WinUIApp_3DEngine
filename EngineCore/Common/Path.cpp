#include "pch.h"
#include "Path.h"

namespace Engine
{	
	std::wstring Path::EngineDir;
	std::wstring Path::ProjectDir;
	std::wstring Path::ProjectName;

	std::wstring Path::DefaultProjectPath;

	void Path::InitDefaultPathes()
	{		
		//EngineDir = winrt::Windows::ApplicationModel::Package::Current().InstalledLocation().Path();
		//���� �ɼ����Ͽ��� �ε��ϴ°ɷ� �ٲ��ֱ�
		ProjectDir = L"D:\\StudyDir\\WinUI_3DEngine\\TestProject";
		//ProjectDir = L"D:\\DX11Engine\\TestProject";
		ProjectName = L"TestProject.DLL";
		DefaultProjectPath = ProjectDir + L"\\x64\\Debug\\" + ProjectName;
	}
}