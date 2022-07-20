#include "EngineMinimal.h"
#include "ComponentBase.h"
#include "ComponentBaseImpl.h"
namespace Engine
{		
	namespace Component 
	{
		ComponentBase::ComponentBase(const std::string& name, SceneComponentType type)
			:pImpl(nullptr)
		{
			pImpl = new ComponentBaseImpl(name, type);
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
		const TransformGroup& ComponentBase::GetComponentTransform()
		{
			return pImpl->GetComponentTransform();
			// // O: 여기에 return 문을 삽입합니다.
		}
		void ComponentBase::UpdateComponentTransform(const TransformGroup* parent)
		{
			pImpl->UpdateComponentTransform( parent );
		}

		SceneComponentType ComponentBase::ComponentType()
		{
			return pImpl->ComponentType();
		}

		//RUNTIME_CLASS_IMPL(DrawableComponent)
	}
}

