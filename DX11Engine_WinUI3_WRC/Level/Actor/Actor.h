#pragma once
//ComponentType�� ���⿡ �����ϸ� component�� ����Ǹ� actor�� ����ǰ� actor�� ����Ǹ� actor�� �������ִ� ������� ��ΰ� �����
//enum�� �����ص� ���������� �̰� �����.
//component�� enum�� �����ϴ��� �����ε�.. �и��ϴ°� �´°Ű���.
//#include "Component/ComponentName.h"
#include "PropertyActor.h"
//���� / ���� Ŭ������ �ϴ� �ϳ��� ���ĳ���, �����ϴ°��� ���� Ŭ������ ���� / ���� ��������. �ٵ� Actor�� �������⼭ ���� ���ϼ��� �־ �����°� ��������.

namespace Engine
{
	namespace Component
	{
		class ActorComponent;
		enum class ActorComponentType;
	}

	namespace Level
	{
		/*	�������̽��� �����Ұ�쿡�� Actor�� ��ӹ޴� ��� Ŭ���� �ȿ��� Update, Render ������ �ٽ� �����ؾ���. ������ �����ؾ��ϴµ�? �� ��ü ���� �ٸ�
			������ �Ӽ����� �����Ҷ� �������̽��� ��ӹ��� ��� Ŭ�������� �ش� �Ӽ����� ���� �����������. enable�̳� visible�� ����Ȱű� ������ �ٽ� ������ �ʿ䰡����.
			�Ӽ���ó�� ���������� ������ ��� �ִ� �༮�� �������� �������̽��� ����������.
			��������� Actor�� handle Ŭ����
			��� actor�� DrawAble�̶�� �����ϱ�. 
		*/
		class Actor
		{
		public:						
			//�Ҹ���
			virtual ~Actor(){};

			//Draw ���� �Լ�
			virtual void Update(float elasedTime) = 0;			

			
			//�ʼ������� ��ӽ��Ѿ��� ���۵�	
			void Init();

			template<typename T>
			std::shared_ptr<T> GetActorComponent(Component::ActorComponentType componentType)
			{
				auto iter = Components.find(componentType);
				if (iter != Components.end())
					return static_cast<shared_ptr<T>>(iter->second);

				return nullptr;
			}

			//Properties
			bool IsEnable() const { return m_PropActor.Enable; }
			void SetEnable(bool enable) { m_PropActor.Enable = enable; }
			bool IsVisible() const { return m_PropActor.Visible; }
			void SetVisible(bool visible) { m_PropActor.Visible = visible; }
			UINT GetLayerMask() const { return m_PropActor.LayerMask; }
			void SetLayerMask(UINT layerMask) { m_PropActor.LayerMask = layerMask; }

			
		private:
			PropertyGroup::PropertyActor m_PropActor;
			//1. ����� �ε����� ����.(������ capacity ���� ����)
			//2. ������ ã�ƿ��� ��(�˻��ð��� ������. �ٵ� ������Ʈ ������ �������� ��� �̰� �����Ű���)
			std::map<Component::ActorComponentType, std::shared_ptr<Component::ActorComponent>> Components;
			//Actor�� component�� Value�� ����Ǹ� delegate�� ����� �Լ��� ȣ���
			//Actor�� �⺻������ Actor������Ʈ�� ������ ����
			//��� ���ʹ� drawable�̴�. �����ͻ󿡼� ���͸� ��Ÿ������ sprite�� ���ؼ� ��Ÿ���⋚��. ���� ��忡���� visible�� false�� �Ǵ� ���͵��� �ְ� �ƴ� ���͵��� �ִ�.
		};
	}
}
