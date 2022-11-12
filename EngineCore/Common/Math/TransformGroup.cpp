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
			//내가원하는 동작은 바깥의 Positon property를 Onchange를 부르면 등록한 callback(이경우에는 

			//property가 Onchage를 호출하면 등록된 Delegate들을 호출
			//OnchagedTransform을 Property의 Onchage에 bind 시켜야됨

			//std::function<void(EngineProperty*)> OnChange = TransformGroup::OnChangeTransorm;			
			//Position.OnChange = std::bind(&TransformGroup::OnChangeTransorm, this, std::placeholders::_1);
			//Rotation.OnChange = std::bind(&TransformGroup::OnChangeTransorm, this, std::placeholders::_1);
			//Scale.OnChange = std::bind(&TransformGroup::OnChangeTransorm, this, std::placeholders::_1);

			//pos에 Value에 =연산자로 넣으면 onchanged 함수 불림.
			//onchanged&SetTransform은 UI에서 property 제어할때만 적용됨						
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
		//	// TODO: 여기에 return 문을 삽입합니다.
		//	pImpl->Identity();
		//}

		////void TransformGroup::OnChangeTransorm(EngineProperty* property)
////{
////	UpdateTransform();
////}
	}


}