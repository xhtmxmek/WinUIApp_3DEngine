#pragma once
#include "PointerActionResult.g.h"
#include "UIProxy/ActorProxy.h"

namespace winrt::EngineInterface_WRC::implementation
{
    struct PointerActionResult : PointerActionResultT<PointerActionResult>
    {
        PointerActionResult() = default;

        winrt::EngineInterface_WRC::ActorProxy PickedActor();
        void PickedActor(winrt::EngineInterface_WRC::ActorProxy const& value);
    private:
        EngineInterface_WRC::ActorProxy pickedActor_;
    };
}
namespace winrt::EngineInterface_WRC::factory_implementation
{
    struct PointerActionResult : PointerActionResultT<PointerActionResult, implementation::PointerActionResult>
    {
    };
}
