#pragma once
#include "DLLDefine.h"
#include "Common/RuntimeContext.h"
#include "Common/Math/TransformGroup.h"
#include "../ComponentTypes.h"

//Component�� �̸��� �߰��Ǵ°��� �������� �ƴϱ⿡, �����ϰ��ִ� ��� ����� ����Ǵ°� ��¿�����°Ͱ���
//Component���� type�� �ʿ� ������ ���ֱ�. �ʿ��ϸ� �߰��ϱ�.
namespace Engine
{
	namespace Level
	{
		class Actor;
	}
	namespace Math
	{
		class TransformGroup;
	}

	namespace Component
	{		
		enum class SceneComponentType;		
		class DrawableComponentImpl;

		class ENGINE_API ComponentBase
		{
		public:
			//RUNTIME_ABSTRACT_ROOT_CLASS(ComponentBase)
		public:
			ComponentBase(const std::string& name, SceneComponentType type);
			virtual ~ComponentBase();
			virtual void Init() = 0;
			virtual void Tick(float elasedTime) = 0;

			void SetPosition(DirectX::SimpleMath::Vector3 const& pos);
			void SetScale(DirectX::SimpleMath::Vector3 const& scale);
			void SetRotation(DirectX::SimpleMath::Vector3 const& rot);
			DirectX::SimpleMath::Vector3 GetRotation();
			const Math::TransformGroup& GetComponentTransform();
			void UpdateComponentTransform(const Math::TransformGroup* parent);

			SceneComponentType ComponentType();

			SharedPointer<ComponentBase> GetParent() { return Parent; }
			List<SharedPointer<ComponentBase>>& GetChildren() { return Children; }
		protected:
			Engine::Level::Actor* Owner;
		private:			
			String Name;
			SharedPointer<Component::ComponentBase> Parent;
			List<SharedPointer<ComponentBase>> Children;
			Math::TransformGroup Transform;
			bool Enable;
			SceneComponentType Type;

		};

		class ENGINE_API DrawableComponent : public ComponentBase
		{
		public:
			//RUNTIME_ABSTRACT_SUB_CLASS(DrawableComponent, ComponentBase)
			DrawableComponent(const std::string& name) : Visible(true), ComponentBase(name, SceneComponentType::Drawable){}
			//DrawableComponent(const std::string& name);
			virtual void Draw() = 0;
			void SetVisible(bool visible) { Visible = visible; }
			bool IsVisible() { return Visible; }
		private:
			DrawableComponentImpl* pImpl;
			bool		Visible;
			//DrawLayer	ComponentDrawLayer;
		};
	}
	
	typedef std::shared_ptr<Component::ComponentBase> ComponentPtr;
}