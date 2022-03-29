#include "pch.h"
#include "ComponentTypes.h"
#include "TransformGroup.h"

namespace Engine
{
	namespace Component
	{		
		TransformGroup::TransformGroup()
			:Position("Position", PropertyType::TypeVector3, Vector3(0, 0, 0)),
			Rotation("Rotation", PropertyType::TypeVector3, Vector3(0, 0, 0)),
			Scale("Position", PropertyType::TypeVector3, Vector3(1, 1, 1))
		{
			//�������ϴ� ������ �ٱ��� Positon property�� Onchange�� �θ��� ����� callback(�̰�쿡�� 

			//property�� Onchage�� ȣ���ϸ� ��ϵ� Delegate���� ȣ��
			//OnchagedTransform�� Property�� Onchage�� bind ���Ѿߵ�

			//std::function<void(EngineProperty*)> OnChange = TransformGroup::OnChangeTransorm;			
			Position.OnChange = std::bind(&TransformGroup::OnChangeTransorm, this, std::placeholders::_1);
			Rotation.OnChange = std::bind(&TransformGroup::OnChangeTransorm, this, std::placeholders::_1);
			Scale.OnChange = std::bind(&TransformGroup::OnChangeTransorm, this, std::placeholders::_1);
		
			//pos�� Value�� =�����ڷ� ������ onchanged �Լ� �Ҹ�.
			//onchanged&SetTransform�� UI���� property �����Ҷ��� �����			
		}
		const Vector3& TransformGroup::GetPosition() const
		{
			return Position.GetValue();
		}
		const Vector3& TransformGroup::GetScale() const
		{
			return Scale.GetValue();
		}
		const Vector3& TransformGroup::GetRotation() const
		{
			return Rotation.GetValue();
		}
		void TransformGroup::SetPosition(const Vector3& pos)
		{
			Position = pos;
			UpdateTransform();
		}
		void TransformGroup::SetScale(const Vector3& scale)
		{
			Scale = scale;
			UpdateTransform();
		}
		void TransformGroup::SetRotation(const Vector3& rotation)
		{
			Rotation = rotation;
			UpdateTransform();
		}
		void TransformGroup::OnChangeTransorm(EngineProperty* property)
		{
			UpdateTransform();
		}
		void TransformGroup::UpdateTransform()
		{
			Matrix m1 = Matrix::CreateTranslation(Position());
			Matrix m2 = Matrix::CreateScale(Scale());
			
			Local = Matrix::CreateScale(Scale()) * Matrix::CreateFromYawPitchRoll(Rotation()) * Matrix::CreateTranslation(Position());
			//�θ� ������쿡
			World = Local;
		}
	}
}