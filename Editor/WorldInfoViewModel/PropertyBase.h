#pragma once
#include "PropertyBase.g.h"
#include "ValueChangedCallbackObject.h"

namespace winrt::Editor::implementation
{
    struct PropertyBase : PropertyBaseT<PropertyBase, Editor::implementation::ValueChangedCallbackObject>
    {
        PropertyBase() = default;
    };
}
