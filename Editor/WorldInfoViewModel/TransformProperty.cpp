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
            /*�ش� property�� ��ȿ�Ҷ�(���λ����Ǿ����� ���� ������ �����ϋ� Property�� �������� �ݿ��Ѵ�.
            * 1)valueChanged���� PropertyChanged ȣ��. PropertyChangedȣ��� Component���� �ݿ�
            * 
            * 2)valueChanged ȣ��� NativeTransform ����. nativeTransform���� �������־���ϴ����� �����.
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
