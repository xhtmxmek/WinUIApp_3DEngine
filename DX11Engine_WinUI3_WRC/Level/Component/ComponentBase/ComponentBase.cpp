#include "EngineMinimal.h"
#include "ComponentBase.h"
#include "ComponentBaseImpl.h"
//#include "Level/Actor/Actor.h"
//#include "Level/World.h"

namespace Engine
{		
	namespace Component 
	{
		ComponentBase::ComponentBase(const std::string& name, SceneComponentType type)
			:pImpl(nullptr)
			,Owner(nullptr)
		{
			pImpl = new ComponentBaseImpl(name, type);
		}

		ComponentBase::~ComponentBase()
		{
			delete pImpl;
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
			return pImpl->GetRotation();
		}
		const Math::TransformGroup& ComponentBase::GetComponentTransform()
		{
			return pImpl->GetComponentTransform();
			// // O: 여기에 return 문을 삽입합니다.
		}
		void ComponentBase::UpdateComponentTransform(const Math::TransformGroup* parent)
		{
			//자기자신의 transform update
			pImpl->UpdateComponentTransform(parent);

			//자식의 transform 업데이트
			std::for_each(pImpl->GetChildren().begin(), pImpl->GetChildren().end(),
				[this](std::shared_ptr<ComponentBase>& component) {
					ComponentBase* child = component.get();
					if (child)
						child->UpdateComponentTransform(&pImpl->GetComponentTransform());
				});			
		}

		SceneComponentType ComponentBase::ComponentType()
		{
			return pImpl->ComponentType();
		}

		//DrawableComponent::DrawableComponent(const std::string& name)
		//	:ComponentBase(name, SceneComponentType::Drawable)
		//{

		//}

		//RUNTIME_CLASS_IMPL(DrawableComponent)
	}
}

