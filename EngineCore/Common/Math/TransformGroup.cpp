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
			scale_(L"Scale", L"Transform", Vector3f(1.f, 1.f, 1.f))
		{
			//내가원하는 동작은 바깥의 Positon property를 Onchange를 부르면 등록한 callback(이경우에는 

			/*std::function<void(Component::PropertyBase*)> Test = */
			position_.BindChangedEvent(std::bind(
				[this](Component::PropertyBase*)
				{
					UpdateTransform();
				}, std::placeholders::_1));

			rotation_.BindChangedEvent(std::bind(
				[this](Component::PropertyBase*)
				{
					UpdateTransform();
				}, std::placeholders::_1));

			scale_.BindChangedEvent(std::bind(
				[this](Component::PropertyBase*)
				{
					UpdateTransform();
				}, std::placeholders::_1));						
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
		//	// TODO: 여기에 return 문을 삽입합니다.
		//	pImpl->Identity();
		//}

		////void TransformGroup::OnChangeTransorm(EngineProperty* property)
////{
////	UpdateTransform();
////}
	}


}