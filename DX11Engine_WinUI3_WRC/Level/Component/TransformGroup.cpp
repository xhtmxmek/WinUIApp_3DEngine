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
			//내가원하는 동작은 바깥의 Positon property를 Onchange를 부르면 등록한 callback(이경우에는 

			//property가 Onchage를 호출하면 등록된 Delegate들을 호출
			//OnchagedTransform을 Property의 Onchage에 bind 시켜야됨

			//std::function<void(EngineProperty*)> OnChange = TransformGroup::OnChangeTransorm;			
			Position.OnChange = std::bind(&TransformGroup::OnChangeTransorm, this, std::placeholders::_1);
			Rotation.OnChange = std::bind(&TransformGroup::OnChangeTransorm, this, std::placeholders::_1);
			Scale.OnChange = std::bind(&TransformGroup::OnChangeTransorm, this, std::placeholders::_1);
		
			//pos에 Value에 =연산자로 넣으면 onchanged 함수 불림.
			//onchanged&SetTransform은 UI에서 property 제어할때만 적용됨			
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
			//부모가 없을경우에
			World = Local;
		}
	}
}