#include "pch.h"
#include "Common/pImplClassDefine.h"
#include "ComponentBase.h"

namespace Engine
{		
	namespace Component 
	{
		ComponentBase::ComponentBase(const std::string& name, SceneComponentType type)
			:owner_(nullptr)
		{			
		}

		ComponentBase::~ComponentBase()
		{		
		}

		void ComponentBase::SetPosition(Vector3f const& pos)
		{
			//Transform.SetPosition(pos);
		}
		void ComponentBase::SetScale(Vector3f const& scale)
		{
			//Transform.SetScale(scale);
		}
		void ComponentBase::SetRotation(Vector3f const& rot)
		{
			//Transform.SetRotation(rot);
		}
		Vector3f ComponentBase::GetRotation()
		{
			return transform_.GetRotation();
		}
		const Math::TransformGroup& ComponentBase::GetComponentTransform()
		{
			return transform_;
		}
		void ComponentBase::UpdateComponentTransform(const Math::TransformGroup* parent)
		{						
			//Children.GetListData
			//�ڽ��� transform ������Ʈ
			//std::shared_ptr<int> test;
			//if (test)
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

		//DrawableComponent::DrawableComponent(const std::string& name)
		//	:ComponentBase(name, SceneComponentType::Drawable)
		//{

		//}

		//RUNTIME_CLASS_IMPL(DrawableComponent)
	}
}

