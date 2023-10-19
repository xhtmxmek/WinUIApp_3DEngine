#include "pch.h"
#include "TransformProperty.h"
#include "Vector3Single.h"
#include "TransformProperty.g.cpp"


namespace winrt::Editor::implementation
{
    TransformProperty::TransformProperty(hstring const& name)
        :name_(name), 
        position_(0.f, 0.f, 0.f),
        propertyVisible_(Microsoft::UI::Xaml::Visibility::Visible)
    {
     
    }

    hstring TransformProperty::Name()
    {
        return name_;
    }

    Editor::Vector3Single TransformProperty::Position()
    {
        return position_;
    }

    void TransformProperty::Position(Editor::Vector3Single const& value)
    {
        if (position_ != value)
        {
            position_.SetValue(value.X(), value.Y(), value.Z());
            //PropertyChanged([this] {
            //    *this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"Position" }; 
            //    });


/*            position_.ValueChanged([]
                {
                    
                })*/;
            /*해당 property가 유효할때(새로생성되었을떄 말고 생성된 상태일떄 Property의 변경점을 반영한다.
            * 1)valueChanged에서 PropertyChanged 호출. PropertyChanged호출시 Component에서 반영
            * 
            * 2)valueChanged 호출시 NativeTransform 변경. nativeTransform까지 가지고있어야하는지가 고민임.
            */
            //positionChangedToken =  position_.ValueChanged([] {
            //    auto engine = Engine::GetRenderingEngine();
            //    });
        }
    }

    winrt::Microsoft::UI::Xaml::Visibility TransformProperty::PropertyVisible()
    {
        return propertyVisible_;
    }

    void TransformProperty::PropertyVisible(winrt::Microsoft::UI::Xaml::Visibility const& value)
    {
        if (propertyVisible_ != value)
        {
            propertyVisible_ = value;
            //PropertyChanged([this] {
            //    *this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ L"PropertyVisible" };
            //    });
        }
    }
}
