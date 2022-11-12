#include "pch.h"
//#include "ComponentTypes.h"
#include "TransformGroup.h"

namespace Engine
{
	namespace Math
	{
		//const TransformGroup TransformGroup::Identity;

		TransformGroup::TransformGroup()
			:position_(Vector3f(0.f, 0.f, 0.f)),
			rotation_(Vector3f(0.f, 0.f, 0.f)),
			scale_(Vector3f(1.f, 1.f, 1.f))
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

		const Vector3f& TransformGroup::GetPosition()
		{
			return position_.Value();
		}

		const Vector3f& TransformGroup::GetScale()
		{
			scale_.Value();
		}

		const Vector3f& TransformGroup::GetRotation()
		{
			rotation_.Value();
		}

		void TransformGroup::UpdateTransform(TransformGroup* parent)
		{						
			localMatrix_ = Matrix4x4f(scale_.Value(), Quaterniont(rotation_.Value().y, rotation_.Value().x, rotation_.Value().z), position_.Value());

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