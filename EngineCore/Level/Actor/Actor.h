#pragma once

#include "DLLDefine.h"
#include "PropertyActor.h"
#include "Common/RuntimeContext.h"	//Class �̸� ������ ������� RunTimeContext ����� ��������. RuntimeContext�� ������ ���� ������ ����.
#include "Component/ComponentLinker.h"

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
				:rootComponent_(nullptr),
				Name("")
			{}

			ENGINE_API virtual ~Actor() = default;

			ENGINE_API virtual void Init() = 0;

			//Draw ���� �Լ�
			ENGINE_API virtual void Tick(float elasedTime) = 0;

			template<typename T>
			std::shared_ptr<T> CreateComponent(const std::string& InstanceName)
			{				
				std::string runTimeClassName = T::ClassName();
				auto newComponent = std::static_pointer_cast<T>(CreateComponent(runTimeClassName, InstanceName));
				//Component::ComponentLink<T>(newComponent);				
				Component::ComponentDispatch(this, newComponent);
				return std::shared_ptr<T>(std::static_pointer_cast<T>(CreateComponent(runTimeClassName, InstanceName)));				
				//������ Ŭ������ ���忡 �־��ָ�, ���尡 ���ø� ������� ������Ʈ�� ������ ���� �ʳ�? �ƴϸ� Ư��ȭ��������.
				//������Ʈ ��Ŀ�� ������Ʈ�� ���� �Ӹ� �ƴ϶� �ٸ������� �������ټ��� ������.. �ϴܿ��常.

			}
			

			std::map<const char*, std::shared_ptr<Component::ComponentBase>>& Components()
			{
				return components_;
			}

			template<typename T>
			std::shared_ptr<T> GetActorComponent(const std::string& name)
			{
				return std::static_pointer_cast<T>(GetComponentByName(name));
			}

			ENGINE_API std::shared_ptr<Component::ComponentBase> GetComponentByName(const std::string& name)
			{
				auto iter = components_.find(name.c_str());
				if (iter != components_.end())
					return iter->second;

				return nullptr;
			}

			ENGINE_API void SetRootComponent(Component::ComponentBase* component){ rootComponent_ = component; }
			ENGINE_API std::shared_ptr<World> GetWorld();

			ENGINE_API std::vector<std::shared_ptr<Level::Actor>>& Children()
			{
				return children_;
			}

			std::string& GetName()
			{
				return Name;
			}

		private:
			std::vector<std::shared_ptr<Level::Actor>> children_;
			std::shared_ptr<Component::ComponentBase> CreateComponent(const std::string& className, const std::string& instanceName);
			//��Ʈ ������Ʈ : ���͸� ��ǥ�ϴ� ������Ʈ. ������Ʈ ����Ʈ�߿� �ϳ��� ����Ŵ
			Component::ComponentBase* rootComponent_;			
			std::map<const char*, std::shared_ptr<Component::ComponentBase>> components_;
			std::string Name;			
		};
	}
}

//#include "Actor.hpp"
