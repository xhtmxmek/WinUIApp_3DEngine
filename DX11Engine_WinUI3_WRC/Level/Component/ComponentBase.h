#pragma once
#include "DLLDefine.h"
#include "Common/RuntimeContext.h"
#include "../TransformGroup/TransformGroup.h"
#include "ComponentTypes.h"

//Component의 이름이 추가되는것은 흔한일이 아니기에, 포함하고있는 모든 헤더가 빌드되는건 어쩔수없는것같음
//Component에서 type이 필요 없으면 뺴주기. 필요하면 추가하기.
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

			//component 생성시에 component의 타입을 명시해줘야 하고, component를 얻어올떄 component의 타입명시를 해야한다.
			//component 생성시에는 각 상속받은 클래스에서 actor를 포함하고 있고, 얻어올떄도 actor를 헤더포함해야한다.
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