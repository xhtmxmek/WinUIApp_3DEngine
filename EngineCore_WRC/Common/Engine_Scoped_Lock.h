#pragma once
#include "Engine_Scoped_Lock.g.h"
#include "EngineCriticalSection.h"

namespace winrt::DX11Engine_WinUI3_WRC::implementation
{
    struct Engine_Scoped_Lock : Engine_Scoped_LockT<Engine_Scoped_Lock>
    {
        Engine_Scoped_Lock() = default;
        Engine_Scoped_Lock(winrt::DX11Engine_WinUI3_WRC::EngineCriticalSection const& mutex);
        ~Engine_Scoped_Lock();        
    private:
        winrt::DX11Engine_WinUI3_WRC::EngineCriticalSection m_mutex{ nullptr };

    };
}
namespace winrt::DX11Engine_WinUI3_WRC::factory_implementation
{
    struct Engine_Scoped_Lock : Engine_Scoped_LockT<Engine_Scoped_Lock, implementation::Engine_Scoped_Lock>
    {
    };
}
