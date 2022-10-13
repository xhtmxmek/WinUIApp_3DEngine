#pragma once

#include "DLLDefine.h"
#include "PropertyActor.h"
#include "Common/RuntimeContext.h"	//Class 이름 정보를 얻기위해 RunTimeContext 헤더를 포함했음. RuntimeContext는 어차피 거의 변하지 않음.
#include "Level/Component/ComponentLinker.h"

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
		
		class Actor
		{								
		public:
			ENGINE_API Actor(const std::string& name)
				:RootComponent(nullptr),
				Name("")
			{}

			ENGINE_API virtual ~Actor() = default;

			ENGINE_API virtual void Init() = 0;

			//Draw 관련 함수
			ENGINE_API virtual void Tick(float elasedTime) = 0;

			template<typename T>
			std::shared_ptr<T> CreateComponent(const std::string& InstanceName)
			{				
				std::string runTimeClassName = T::ClassName();
				auto newComponent = std::static_pointer_cast<T>(CreateComponent(runTimeClassName, InstanceName));
				//Component::ComponentLink<T>(newComponent);				
				Component::ComponentDispatch(this, newComponent);
				return std::shared_ptr<T>(std::static_pointer_cast<T>(CreateComponent(runTimeClassName, InstanceName)));				
				//생성된 클래스를 월드에 넣어주면, 월드가 템플릿 기반으로 컴포넌트를 받으면 되지 않나? 아니면 특수화버전으로.
				//컴포넌트 링커는 컴포넌트를 월드 뿐만 아니라 다른곳에도 연결해줄수도 있을듯.. 일단월드만.

			}

			template<typename T>
			std::shared_ptr<T> GetActorComponent(const std::string& name)
			{
				return std::static_pointer_cast<T>(GetActorComponent(name));
			}

			ENGINE_API std::shared_ptr<Component::ComponentBase> GetComponentByName(const std::string& name)
			{
				auto iter = Components.find(name.c_str());
				if (iter != Components.end())
					return iter->second;

				return nullptr;
			}

			ENGINE_API void SetRootComponent(Component::ComponentBase* component){ RootComponent = component; }
			ENGINE_API std::shared_ptr<World> GetWorld();

		private:
			std::shared_ptr<Component::ComponentBase> CreateComponent(const std::string& className, const std::string& instanceName);
			//루트 컴포넌트 : 액터를 대표하는 컴포넌트. 컴포넌트 리스트중에 하나를 가리킴
			Component::ComponentBase* RootComponent;			
			std::map<const char*, std::shared_ptr<Component::ComponentBase>> Components;
			std::string Name;			
		};
	}
}

//#include "Actor.hpp"
