#pragma once
#include "ValueChangedCallbackObject.h"
#include "Vector3Single.g.h"


namespace winrt::Editor::implementation
{
    struct Vector3Single : Vector3SingleT<Vector3Single, Editor::implementation::ValueChangedCallbackObject>
    {
        Vector3Single() = delete;

        Vector3Single(float x, float y, float z);

        void SetValue(float x, float y, float z);

        float X();
        void X(float value);
        float Y();
        void Y(float value);
        float Z();
        void Z(float value);
    private:
        Windows::Foundation::Numerics::float3 value_;
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> propertyChangedTest_;
    };
}
namespace winrt::Editor::factory_implementation
{
    struct Vector3Single : Vector3SingleT<Vector3Single, implementation::Vector3Single>
    {
    };
}
