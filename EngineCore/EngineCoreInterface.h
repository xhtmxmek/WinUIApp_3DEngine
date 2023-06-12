#pragma once

#include "DLLDefine.h"

namespace SharedTypes
{
    enum class VirtualKey;
    enum class PointerButton;
}

namespace Engine
{
    class EngineCore;

    ENGINE_API EngineCore* GetEngineCore();
    ENGINE_API void DestroyEngineCore();
}