#include "EngineMinimal.h"
#include "EngineCriticalSection.h"
#include "EngineCriticalSection.g.cpp"

namespace winrt::DX11Engine_WinUI3_WRC::implementation
{
	void EngineCriticalSection::Lock()
	{
		m_criticalSection.lock();
	}
	void EngineCriticalSection::UnLock()
	{
		m_criticalSection.unlock();
	}
}
