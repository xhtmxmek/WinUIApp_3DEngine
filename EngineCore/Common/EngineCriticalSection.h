#pragma once
#include "EngineCriticalSection.g.h"

namespace winrt::DX11Engine_WinUI3_WRC::implementation
{
    struct EngineCriticalSection : EngineCriticalSectionT<EngineCriticalSection>
    {
        EngineCriticalSection() = default;
        void Lock();
        void UnLock();
        concurrency::critical_section m_criticalSection;        
    };
}
namespace winrt::DX11Engine_WinUI3_WRC::factory_implementation
{
    struct EngineCriticalSection : EngineCriticalSectionT<EngineCriticalSection, implementation::EngineCriticalSection>
    {
    };
}
