#pragma once
#include "DLLDefine.h"
#include "Common/RuntimeContext.h"
#include "../TransformGroup/TransformGroup.h"
#include "ComponentTypes.h"

//Component�� �̸��� �߰��Ǵ°��� �������� �ƴϱ⿡, �����ϰ��ִ� ��� ����� ����Ǵ°� ��¿�����°Ͱ���
//Component���� type�� �ʿ� ������ ���ֱ�. �ʿ��ϸ� �߰��ϱ�.
namespace Engine
{
	namespace Component
	{		
		enum class SceneComponentType;
		class ComponentBaseImpl;
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
			const Level::TransformGroup& GetComponentTransform();
			void UpdateComponentTransform(const Level::TransformGroup* parent);
			SceneComponentType ComponentType();
		private:
			ComponentBaseImpl* pImpl;
			//std::list<std::shared_ptr<ComponentBase>> Child;
			//std::shared_ptr<ComponentBase> Parent;
			//std::map<PropertyName, EngineProperty*> Properties;

			//component �����ÿ� component�� Ÿ���� �������� �ϰ�, component�� ���Ë� component�� Ÿ�Ը�ø� �ؾ��Ѵ�.
			//component �����ÿ��� �� ��ӹ��� Ŭ�������� actor�� �����ϰ� �ְ�, ���Ë��� actor�� ��������ؾ��Ѵ�.
			//component 
		};

		class ENGINE_API DrawableComponent : public ComponentBase
		{
		public:
			//RUNTIME_ABSTRACT_SUB_CLASS(DrawableComponent, ComponentBase)
			DrawableComponent(const std::string& name): Visible(true), ComponentBase(name, SceneComponentType::Drawable) {}
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