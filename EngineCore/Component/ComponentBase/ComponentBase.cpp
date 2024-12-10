#include "pch.h"
#include "Common/pImplClassDefine.h"
#include "ComponentBase.h"

namespace Engine
{		
	namespace Component 
	{
		ComponentBase::ComponentBase(const std::string& name, SceneComponentType type)
			:name_(name),
			type_(type), 
			owner_(nullptr)
		{			
		}

		ComponentBase::~ComponentBase()
		{		
		}

		void ComponentBase::SetPosition(Vector3f const& pos)
		{
			transform_.SetPosition(pos);
			UpdateComponentTransform();
		}
		void ComponentBase::SetScale(Vector3f const& scale)
		{
			transform_.SetScale(scale);
			UpdateComponentTransform();
		}
		void ComponentBase::SetRotation(Vector3f const& rot)
		{
			transform_.SetRotation(rot);
			UpdateComponentTransform();
		}
		const Vector3f ComponentBase::GetRotation()
		{
			return transform_.GetRotation();
		}
		Math::TransformGroup& ComponentBase::GetComponentTransform()
		{
			return transform_;
		}
		void ComponentBase::UpdateComponentTransform(const Math::TransformGroup* parent)
		{						
			transform_.UpdateTransform(parent);

			std::for_each(children_.begin(), children_.end(),
				[this](shared_ptr<ComponentBase>& component) {					
					//ComponentBase* child = component.Get();					
					if (component != nullptr)
						component->UpdateComponentTransform(&transform_);
				});			
		}

		SceneComponentType ComponentBase::ComponentType()
		{
			return type_;
		}

		void ComponentBase::AddProperty(PropertyBase* newProperty)
		{
			properties_.push_back(newProperty);
		}

		//void ComponentBase::AddProperty(const shared_ptr<ProperyBase>& property)
		//{
		//	properties_.push_back(property);
		//}

		//DrawableComponent::DrawableComponent(const std::string& name)
		//	:ComponentBase(name, SceneComponentType::Drawable)
		//{

		//}

		DrawableComponent::DrawableComponent(const std::string& name)
			:visible_(L"visible", L"Rendering"), ComponentBase(name, SceneComponentType::Drawable)
		{	

			AddProperty(&visible_);
			visible_.BindChangedEvent([this](PropertyBase* base)
				{
					int k = 5;
				});
		}
	}
}

