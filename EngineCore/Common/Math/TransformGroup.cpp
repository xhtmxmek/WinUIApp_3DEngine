#include "pch.h"
//#include "ComponentTypes.h"
#include "TransformGroup.h"

namespace Engine
{
	namespace Math
	{
		//const TransformGroup TransformGroup::Identity;

		TransformGroup::TransformGroup()
			:position_(L"Position", L"Transform"),
			rotation_(L"Rotation", L"Transform"),
			scale_(L"Scale", L"Transform")
		{
			//�������ϴ� ������ �ٱ��� Positon property�� Onchange�� �θ��� ����� callback(�̰�쿡�� 

			//property�� Onchage�� ȣ���ϸ� ��ϵ� Delegate���� ȣ��
			//OnchagedTransform�� Property�� Onchage�� bind ���Ѿߵ�

			//std::function<void(EngineProperty*)> OnChange = TransformGroup::OnChangeTransorm;			
			//Position.OnChange = std::bind(&TransformGroup::OnChangeTransorm, this, std::placeholders::_1);
			//Rotation.OnChange = std::bind(&TransformGroup::OnChangeTransorm, this, std::placeholders::_1);
			//Scale.OnChange = std::bind(&TransformGroup::OnChangeTransorm, this, std::placeholders::_1);

			//pos�� Value�� =�����ڷ� ������ onchanged �Լ� �Ҹ�.
			//onchanged&SetTransform�� UI���� property �����Ҷ��� �����						
		}
		TransformGroup::~TransformGroup()
		{
		}

		Component::PropertyVector3* TransformGroup::GetPosition()
		{
			return &position_;
		}

		Component::PropertyVector3* TransformGroup::GetScale()
		{
			return &scale_;
		}

		Component::PropertyVector3* TransformGroup::GetRotation()
		{
			return &rotation_;
		}

		void TransformGroup::UpdateTransform(const TransformGroup* parent)
		{
			localMatrix_ = Matrix4x4f(scale_(), Quaternionf(rotation_().y, rotation_().z, rotation_().x), position_());

			if (parent)
				worldMatrix_ = localMatrix_ * parent->GetWorldMatrix();
			else
				worldMatrix_ = localMatrix_;
		}

		//TransformGroup const TransformGroup::Default()
		//{
		//	// TODO: ���⿡ return ���� �����մϴ�.
		//	pImpl->Identity();
		//}

		////void TransformGroup::OnChangeTransorm(EngineProperty* property)
////{
////	UpdateTransform();
////}
	}


}