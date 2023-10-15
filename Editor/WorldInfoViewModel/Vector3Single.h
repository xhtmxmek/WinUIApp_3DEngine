#pragma once
#include "Vector3Single.g.h"


namespace winrt::Editor::implementation
{
    struct Vector3Single : Vector3SingleT<Vector3Single>
    {
        Vector3Single() = delete;

        Vector3Single(float x, float y, float z);
        float X();
        void X(float value);
        float Y();
        void Y(float value);
        float Z();
        void Z(float value);
        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);
        void PropertyChanged(winrt::event_token const& token) noexcept;
    private:
        Windows::Foundation::Numerics::float3 value_;
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> propertyChanged_;

    };
}
namespace winrt::Editor::factory_implementation
{
    struct Vector3Single : Vector3SingleT<Vector3Single, implementation::Vector3Single>
    {
    };
}
