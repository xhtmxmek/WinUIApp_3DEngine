#pragma once
#include "DLLDefine.h"
#include "Common/RuntimeContext.h"
#include "ComponentTypes.h"
#include "TransformGroup.h"

//Component의 이름이 추가되는것은 흔한일이 아니기에, 포함하고있는 모든 헤더가 빌드되는건 어쩔수없는것같음
//Component에서 type이 필요 없으면 뺴주기. 필요하면 추가하기.
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

			//component 생성시에 component의 타입을 명시해줘야 하고, component를 얻어올떄 component의 타입명시를 해야한다.
			//component 생성시에는 각 상속받은 클래스에서 actor를 포함하고 있고, 얻어올떄도 actor를 헤더포함해야한다.
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