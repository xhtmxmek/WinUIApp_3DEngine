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
			scale_(L"Scale", L"Transform", Vector3f(1.f, 1.f, 1.f)),
			fowardVector_(0.f, 0.f, 1.f),
			upvector_(0.f, 1.f, 0.f),
			rightVector_(1.f, 0.f, 0.f)
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

		const Vector3f& TransformGroup::GetPosition()
		{
			return position_.Value();
		}

		const Vector3f& TransformGroup::GetScale()
		{
			return scale_.Value();
		}

		const Vector3f& TransformGroup::GetRotation()
		{
			return rotation_.Value();
		}

		Component::PropertyVector3* TransformGroup::GetPositionPtrToEditor()
		{
			return &position_;
		}

		Component::PropertyVector3* TransformGroup::GetScalePtrToEditor()
		{
			return &scale_;
		}

		Component::PropertyVector3* TransformGroup::GetRotationPtrToEditor()
		{
			return &rotation_;
		}

		Vector3f TransformGroup::GetFowardVector()
		{
			return fowardVector_;
		}

		Vector3f TransformGroup::GetRightVector()
		{
			return rightVector_;
		}

		Vector3f TransformGroup::GetUpVector()
		{
			return upvector_;
		}

		void TransformGroup::UpdateTransform(const TransformGroup* parent)
		{
			localMatrix_ = Matrix4x4f(scale_(), Quaternionf(rotation_().y, rotation_().z, rotation_().x), position_());

			if (parent)
				worldMatrix_ = localMatrix_ * parent->GetWorldMatrix();
			else
				worldMatrix_ = localMatrix_;

			fowardVector_ *= worldMatrix_;
			upvector_ *= worldMatrix_;
			rightVector_ *= worldMatrix_;
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