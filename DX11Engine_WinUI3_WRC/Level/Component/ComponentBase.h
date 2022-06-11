#pragma once
#include "DLLDefine.h"
#include "Common/RuntimeContext.h"
#include "ComponentTypes.h"
#include "TransformGroup.h"

//Component�� �̸��� �߰��Ǵ°��� �������� �ƴϱ⿡, �����ϰ��ִ� ��� ����� ����Ǵ°� ��¿�����°Ͱ���
//Component���� type�� �ʿ� ������ ���ֱ�. �ʿ��ϸ� �߰��ϱ�.
namespace Engine
{
	namespace Component
	{		
		class ComponentBase
		{
		public:
			//RUNTIME_ABSTRACT_ROOT_CLASS(ComponentBase)
		public:
			ComponentBase(const std::string& name, SceneComponentType type): Name(name), Enable(true), Type(type) {}
			virtual ~ComponentBase(){}
			virtual void Init() = 0;
			virtual void Tick(float elasedTime) = 0;
			void SetPosition(DirectX::SimpleMath::Vector3 const& pos);
			void SetScale(DirectX::SimpleMath::Vector3 const& scale);
			void SetRotation(DirectX::SimpleMath::Vector3 const& rot);
			const TransformGroup& GetComponentTransform() { return Transform; }
			void UpdateComponentTransform(const TransformGroup* parent);
			SceneComponentType ComponentType() { return Type; }			
		private:
			std::string Name;
			std::shared_ptr<ComponentBase> Parent;
			std::list<std::shared_ptr<ComponentBase>> Child;			
			TransformGroup Transform;
			bool Enable;
			SceneComponentType Type;
			
			//std::map<PropertyName, EngineProperty*> Properties;

			//component �����ÿ� component�� Ÿ���� �������� �ϰ�, component�� ���Ë� component�� Ÿ�Ը�ø� �ؾ��Ѵ�.
			//component �����ÿ��� �� ��ӹ��� Ŭ�������� actor�� �����ϰ� �ְ�, ���Ë��� actor�� ��������ؾ��Ѵ�.
			//component 
		};

		class DrawableComponent : public ComponentBase
		{
		public:
			//RUNTIME_ABSTRACT_SUB_CLASS(DrawableComponent, ComponentBase)
			DrawableComponent(const std::string& name): Visible(true), ComponentBase(name, SceneComponentType::Drawable) {}
			virtual void Draw() = 0;
			void SetVisible(bool visible) { Visible = visible; }
			bool IsVisible() { return Visible; }
		private:
			bool		Visible;
			//DrawLayer	ComponentDrawLayer;
		};
	}
	
	typedef std::shared_ptr<Component::ComponentBase> ComponentPtr;
}