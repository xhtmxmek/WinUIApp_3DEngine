#pragma once
#include "PropertyActor.h"
//���� / ���� Ŭ������ �ϴ� �ϳ��� ���ĳ���, �����ϴ°��� ���� Ŭ������ ���� / ���� ��������. �ٵ� Actor�� �������⼭ ���� ���ϼ��� �־ �����°� ��������.

namespace Engine
{
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
			virtual void Render() = 0;

			//Properties
			//PropActor. �ʼ������� ��ӽ��Ѿ��� ���۵�
			bool IsEnable() const { return m_PropActor.Enable; }
			void SetEnable(bool enable) { m_PropActor.Enable = enable; }
			bool IsVisible() const { return m_PropActor.Visible; }
			void SetVisible(bool visible) { m_PropActor.Visible = visible; }
			UINT GetLayerMask() const { return m_PropActor.LayerMask;  }
			void SetLayerMask(UINT layerMask) { m_PropActor.LayerMask = layerMask; }

			//TransformGroup

		private:
			PropertyGroup::PropertyActor m_PropActor;			
			//TransformGroup
		};
	}
}
