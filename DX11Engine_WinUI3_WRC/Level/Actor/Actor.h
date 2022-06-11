#pragma once

#include "DLLDefine.h"
#include "PropertyActor.h"
#include "Common/RuntimeContext.h"	//Class �̸� ������ ������� RunTimeContext ����� ��������. RuntimeContext�� ������ ���� ������ ����.

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

			//�Ҹ���
			virtual ~Actor() {};

			virtual void Init() = 0;

			//Draw ���� �Լ�
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
			//Actor�� component�� Value�� ����Ǹ� delegate�� ����� �Լ��� ȣ���
			//Actor�� �⺻������ Actor������Ʈ�� ������ ����
			//��� ���ʹ� drawable�̴�. �����ͻ󿡼� ���͸� ��Ÿ������ sprite�� ���ؼ� ��Ÿ���⋚��. ���� ��忡���� visible�� false�� �Ǵ� ���͵��� �ְ� �ƴ� ���͵��� �ִ�.
		};
	}
}

//#include "Actor.hpp"
