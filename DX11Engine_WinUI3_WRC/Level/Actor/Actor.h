#pragma once

#include "DLLDefine.h"
#include "PropertyActor.h"
#include "Common/RuntimeContext.h"	//Class �̸� ������ ������� RunTimeContext ����� ��������. RuntimeContext�� ������ ���� ������ ����.
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
		
		class ENGINE_API Actor
		{								
		public:
			Actor(const std::string& name)
				:RootComponent(nullptr),
				Name("")
			{}

			virtual ~Actor() = default;

			virtual void Init() = 0;

			//Draw ���� �Լ�
			virtual void Tick(float elasedTime) = 0;

			template<typename T>
			SharedPointer<T> CreateComponent(const std::string& InstanceName)
			{				
				std::string runTimeClassName = T::ClassName();
				auto newComponent = std::static_pointer_cast<T>(CreateComponent(runTimeClassName, InstanceName));
				//Component::ComponentLink<T>(newComponent);				
				Component::ComponentDispatch(this, newComponent);
				return SharedPointer<T>(std::static_pointer_cast<T>(CreateComponent(runTimeClassName, InstanceName)));				
				//������ Ŭ������ ���忡 �־��ָ�, ���尡 ���ø� ������� ������Ʈ�� ������ ���� �ʳ�? �ƴϸ� Ư��ȭ��������.
				//������Ʈ ��Ŀ�� ������Ʈ�� ���� �Ӹ� �ƴ϶� �ٸ������� �������ټ��� ������.. �ϴܿ��常.

			}

			template<typename T>
			std::shared_ptr<T> GetActorComponent(const std::string& name)
			{
				return std::static_pointer_cast<T>(GetActorComponent(name));
			}

			SharedPointer<Component::ComponentBase> GetComponentByName(const std::string& name)
			{
				auto iter = Components().find(name.c_str());
				if (iter != Components().end())
					return iter->second;

				return nullptr;
			}

			void SetRootComponent(Component::ComponentBase* component){ RootComponent = component; }
			SharedPointer<World> GetWorld();

		private:
			std::shared_ptr<Component::ComponentBase> CreateComponent(const String& className, const String& instanceName);
			//��Ʈ ������Ʈ : ���͸� ��ǥ�ϴ� ������Ʈ. ������Ʈ ����Ʈ�߿� �ϳ��� ����Ŵ
			Component::ComponentBase* RootComponent;			
			Map<const char*, SharedPointer<Component::ComponentBase>> Components;
			String Name;			
		};
	}
}

//#include "Actor.hpp"
