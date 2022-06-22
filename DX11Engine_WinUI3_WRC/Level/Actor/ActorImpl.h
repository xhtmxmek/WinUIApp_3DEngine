#pragma once
#include "DLLDefine.h"
#include "PropertyActor.h"

namespace Engine
{

	namespace Component
	{
		class ComponentBase;
		enum class ActorComponentType;		
		//class TransformGroup;
	}

	namespace Level
	{
		/*	�������̽��� �����Ұ�쿡�� Actor�� ��ӹ޴� ��� Ŭ���� �ȿ��� Update, Render ������ �ٽ� �����ؾ���. ������ �����ؾ��ϴµ�? �� ��ü ���� �ٸ�
			������ �Ӽ����� �����Ҷ� �������̽��� ��ӹ��� ��� Ŭ�������� �ش� �Ӽ����� ���� �����������. enable�̳� visible�� ����Ȱű� ������ �ٽ� ������ �ʿ䰡����.
			�Ӽ���ó�� ���������� ������ ��� �ִ� �༮�� �������� �������̽��� ����������.
			��������� Actor�� handle Ŭ����
			��� actor�� DrawAble�̶�� �����ϱ�.
		*/
		class World;

		class ActorImpl
		{
		public:
			ActorImpl(const std::string& name, World* rootWorld) :Name(name), RootComponent(nullptr), RootWorld(rootWorld) {};
			
			std::shared_ptr<Component::ComponentBase> GetActorComponentByName(const std::string& name)
			{
				auto iter = Components.find(name);
				if (iter != Components.end())
					return iter->second;

				return nullptr;
			}

			void SetRootComponent(Component::ComponentBase* component)
			{
				RootComponent = component;				
			}
			
			std::shared_ptr<Component::ComponentBase> CreateComponent(const std::string& className, const std::string& instanceName);

			World* GetWorld();

			//Properties
			//bool IsEnable() const { return m_PropActor.Enable; }
			//void SetEnable(bool enable) { m_PropActor.Enable = enable; }
			//bool IsVisible() const { return m_PropActor.Visible; }
			//void SetVisible(bool visible) { m_PropActor.Visible = visible; }
			//UINT GetLayerMask() const { return m_PropActor.LayerMask; }
			//void SetLayerMask(UINT layerMask) { m_PropActor.LayerMask = layerMask; }
			//TransformGroup const& GetTransform();

		private:
			//PropertyGroup::PropertyActor m_PropActor;
			//1. ����� �ε����� ����.(������ capacity ���� ����)
			//2. ������ ã�ƿ��� ��(�˻��ð��� ������. �ٵ� ������Ʈ ������ �������� ��� �̰� �����Ű���)

			World* RootWorld;
			//��Ʈ ������Ʈ : ���͸� ��ǥ�ϴ� ������Ʈ. ������Ʈ ����Ʈ�߿� �ϳ��� ����Ŵ
			Component::ComponentBase* RootComponent;
			//������Ʈ ����Ʈ : ���Ͱ� ������ �ִ� ������Ʈ ����Ʈ. 
			std::map<std::string, std::shared_ptr<Component::ComponentBase>> Components;
			std::string Name;
			//Actor�� component�� Value�� ����Ǹ� delegate�� ����� �Լ��� ȣ���
			//Actor�� �⺻������ Actor������Ʈ�� ������ ����
			//��� ���ʹ� drawable�̴�. �����ͻ󿡼� ���͸� ��Ÿ������ sprite�� ���ؼ� ��Ÿ���⋚��. ���� ��忡���� visible�� false�� �Ǵ� ���͵��� �ְ� �ƴ� ���͵��� �ִ�.
		};
	}
}
