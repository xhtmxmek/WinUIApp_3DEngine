#pragma once
#include "ComponentTypes.h"
#include "TransformGroup.h"

//Component의 이름이 추가되는것은 흔한일이 아니기에, 포함하고있는 모든 헤더가 빌드되는건 어쩔수없는것같음
//Component에서 type이 필요 없으면 뺴주기. 필요하면 추가하기.
namespace Engine
{
	namespace Component
	{							
		class ActorComponent
		{
		public:
			virtual void Init() = 0;
			virtual void Tick(float elasedTime) = 0;			
			void SetPosition(Vector3 const& pos);
			void SetScale(Vector3 const& scale);
			void SetRotation(Vector3 const& rot);
			const TransformGroup& GetComponentTransform() { return Transform; }
			void UpdateComponentTransform(const TransformGroup* parent);
		private:
			std::shared_ptr<ActorComponent> Parent;
			std::list<std::shared_ptr<ActorComponent>> Child;			
			ActorComponentType ComponentType;
			TransformGroup Transform;
			bool		Enable;
			//std::map<PropertyName, EngineProperty*> Properties;
			
			//component 생성시에 component의 타입을 명시해줘야 하고, component를 얻어올떄 component의 타입명시를 해야한다.
			//component 생성시에는 각 상속받은 클래스에서 actor를 포함하고 있고, 얻어올떄도 actor를 헤더포함해야한다.
			//component 
		};

		class DrawableComponent : public ActorComponent
		{
		public:
			virtual void Draw() = 0;
			bool		Visible;
			DrawLayer	ComponentDrawLayer;
		};
	}
}