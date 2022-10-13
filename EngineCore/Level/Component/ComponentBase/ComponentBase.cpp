#include "pch.h"
#include "Common/pImplClassDefine.h"
#include "ComponentBase.h"

namespace Engine
{		
	namespace Component 
	{
		ComponentBase::ComponentBase(const std::string& name, SceneComponentType type)
			:Owner(nullptr)
		{			
		}

		ComponentBase::~ComponentBase()
		{		
		}

		void ComponentBase::SetPosition(Vector3 const& pos)
		{
			//Transform.SetPosition(pos);
		}
		void ComponentBase::SetScale(Vector3 const& scale)
		{
			//Transform.SetScale(scale);
		}
		void ComponentBase::SetRotation(Vector3 const& rot)
		{
			//Transform.SetRotation(rot);
		}
		DirectX::SimpleMath::Vector3 ComponentBase::GetRotation()
		{
			return Transform.GetRotation();
		}
		const Math::TransformGroup& ComponentBase::GetComponentTransform()
		{
			return Transform;			
		}
		void ComponentBase::UpdateComponentTransform(const Math::TransformGroup* parent)
		{						
			//Children.GetListData
			//�ڽ��� transform ������Ʈ
			//std::shared_ptr<int> test;
			//if (test)
			std::for_each(Children.begin(), Children.end(),
				[this](shared_ptr<ComponentBase>& component) {					
					//ComponentBase* child = component.Get();					
					if (component != nullptr)
						component->UpdateComponentTransform(&Transform);
				});			
		}

		SceneComponentType ComponentBase::ComponentType()
		{
			return Type;
		}

		//DrawableComponent::DrawableComponent(const std::string& name)
		//	:ComponentBase(name, SceneComponentType::Drawable)
		//{

		//}

		//RUNTIME_CLASS_IMPL(DrawableComponent)
	}
}

