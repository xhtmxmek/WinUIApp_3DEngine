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

	namespace World
	{
		class World;
		class ActorImpl;
		
		class Actor
		{
		public:
			RUNTIME_ABSTRACT()
		public:
			ENGINE_API Actor(const std::string& name)
				:rootComponent_(nullptr),
				name_(name)
			{}

			ENGINE_API virtual ~Actor() = default;

			ENGINE_API virtual void Init() = 0;

			//Draw ���� �Լ�
			ENGINE_API virtual void Tick(float elasedTime) = 0;
		public:
			template<typename T>
			std::shared_ptr<T> CreateComponent(const std::string& InstanceName)
			{
				std::string runTimeClassName = T::ClassName();
				auto newComponent = std::static_pointer_cast<T>(CreateComponent(runTimeClassName, InstanceName));
				//Component::ComponentLink<T>(newComponent);
				//��ӹ��� Ŭ�������� ������ �ϴ°� �´µ�
				Component::ComponentDispatch(this, newComponent);

				return newComponent;

				//������ Ŭ������ ���忡 �־��ָ�, ���尡 ���ø� ������� ������Ʈ�� ������ ���� �ʳ�? �ƴϸ� Ư��ȭ��������.
				//������Ʈ ��Ŀ�� ������Ʈ�� ���� �Ӹ� �ƴ϶� �ٸ������� �������ټ��� ������.. �ϴܿ��常.

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

			ENGINE_API std::shared_ptr<Component::ComponentBase> GetComponentByIndex(int index)
			{
				if (index >= componentNames_.size())
					return nullptr;

				return GetComponentByName(componentNames_[index]);
			}

			ENGINE_API size_t NumComponent()
			{
				return components_.size();
			}

			ENGINE_API void SetRootComponent(std::shared_ptr<Component::ComponentBase> const& component) { rootComponent_ = component; }
			ENGINE_API std::shared_ptr<Component::ComponentBase> const& GetRootComponent()
			{
				return rootComponent_;
			}


			ENGINE_API std::shared_ptr<World> GetWorld();

			ENGINE_API string Name()
			{
				return name_;
			}
		private:
			std::shared_ptr<Component::ComponentBase> CreateComponent(const std::string& className, const std::string& instanceName);
			//��Ʈ ������Ʈ : ���͸� ��ǥ�ϴ� ������Ʈ. ������Ʈ ����Ʈ�߿� �ϳ��� ����Ŵ
			std::shared_ptr<Component::ComponentBase> rootComponent_;
			std::unordered_map<string, std::shared_ptr<Component::ComponentBase>> components_;
			std::vector<string> componentNames_;
			std::string name_;
		};
	}
}

//#include "Actor.hpp"
