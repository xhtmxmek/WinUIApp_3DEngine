#include "pch.h"
#include "PointerActionResult.h"
#include "PointerActionResult.g.cpp"

namespace winrt::EngineInterface_WRC::implementation
{
    winrt::EngineInterface_WRC::ActorProxy PointerActionResult::PickedActor()
    {
        return pickedActor_;
    }
    void PointerActionResult::PickedActor(winrt::EngineInterface_WRC::ActorProxy const& value)
    {
        pickedActor_ = value;
    }
}
