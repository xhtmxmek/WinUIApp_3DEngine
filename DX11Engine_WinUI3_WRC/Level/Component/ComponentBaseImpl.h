#pragma once
#include "ComponentTypes.h"
#include "TransformGroup.h"

namespace Engine
{
	namespace Component
	{
		class ComponentBase;

		class ComponentBaseImpl
		{
		public:
			ComponentBaseImpl(const std::string& name, SceneComponentType type);
			virtual ~ComponentBaseImpl() {}
			void SetPosition(DirectX::SimpleMath::Vector3 const& pos);
			void SetScale(DirectX::SimpleMath::Vector3 const& scale);
			void SetRotation(DirectX::SimpleMath::Vector3 const& rot);
			DirectX::SimpleMath::Vector3 GetRotation();
			const TransformGroup& GetComponentTransform() { return Transform; }
			void UpdateComponentTransform(const TransformGroup* parent);
			SceneComponentType ComponentType() { return Type; }
			std::shared_ptr<ComponentBase> GetParent() { return Parent; }
			std::list<std::shared_ptr<ComponentBase>>& GetChildren() { return Children; }


		private:
			std::string Name;
			std::shared_ptr<ComponentBase> Parent;
			std::list<std::shared_ptr<ComponentBase>> Children;
			TransformGroup Transform;
			bool Enable;
			SceneComponentType Type;
		};


	}
}
