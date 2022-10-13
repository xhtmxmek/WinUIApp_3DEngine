#include "pch.h"
#include "Engine_Scoped_Lock.h"
#include "Engine_Scoped_Lock.g.cpp"
#include "EngineCriticalSection.h"

namespace winrt::DX11Engine_WinUI3_WRC::implementation
{
	Engine_Scoped_Lock::Engine_Scoped_Lock(winrt::DX11Engine_WinUI3_WRC::EngineCriticalSection const& mutex)
	{		
		m_mutex = mutex;
		m_mutex.Lock();
	}
	Engine_Scoped_Lock::~Engine_Scoped_Lock()
	{
		m_mutex.UnLock();
	}
}
