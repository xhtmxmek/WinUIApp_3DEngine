#pragma once

#include "DLLDefine.h"
#include "PropertyActor.h"
#include "Common/RuntimeContext.h"	//Class 이름 정보를 얻기위해 RunTimeContext 헤더를 포함했음. RuntimeContext는 어차피 거의 변하지 않음.

namespace Engine
{

	namespace Component
	{
		class ComponentBase;		
		class TransformGroup;
	}

	namespace Level
	{
		class World;
		class ActorImpl;

		class ENGINE_API Actor
		{					
		public:
			Actor(const std::string& name, World* rootWorld);

			//소멸자
			virtual ~Actor() {};

			virtual void Init() = 0;

			//Draw 관련 함수
			virtual void Tick(float elasedTime) = 0;

			template<typename T>
			std::shared_ptr<T> CreateComponent(const std::string& InstanceName)
			{				
				std::string runTimeClassName = T::ClassName();
				return std::static_pointer_cast<T>(CreateComponent(runTimeClassName, InstanceName));
			}

			template<typename T>
			std::shared_ptr<T> GetActorComponent(const std::string& name)
			{
				return std::static_pointer_cast<T>(GetActorComponent(name));
			}

			void SetRootComponent(Component::ComponentBase* component);

		private:
			std::shared_ptr<Component::ComponentBase> CreateComponent(const std::string& className, const std::string& instanceName);
			std::shared_ptr<Component::ComponentBase> GetComponentByName(const std::string& name);
			//Impl
			ActorImpl* pImpl;
			
			//std::map<std::string, std::shared_ptr<ComponentBase>> Components;			
			//Actor의 component의 Value가 변경되면 delegate로 연결된 함수가 호출됨
			//Actor는 기본적으로 Actor컴포넌트를 가지고 있음
			//모든 액터는 drawable이다. 에디터상에서 액터를 나타내려면 sprite를 통해서 나타내기떄문. 게임 모드에서는 visible이 false가 되는 액터들이 있고 아닌 액터들이 있다.
		};
	}
}

//#include "Actor.hpp"
