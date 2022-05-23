#pragma once
#include "ComponentTypes.h"
#include "TransformGroup.h"

//Component�� �̸��� �߰��Ǵ°��� �������� �ƴϱ⿡, �����ϰ��ִ� ��� ����� ����Ǵ°� ��¿�����°Ͱ���
//Component���� type�� �ʿ� ������ ���ֱ�. �ʿ��ϸ� �߰��ϱ�.
namespace Engine
{
	namespace Level
	{
		class ComponentBase
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
			std::shared_ptr<ComponentBase> Parent;
			std::list<std::shared_ptr<ComponentBase>> Child;
			//ActorComponentType ComponentType;
			TransformGroup Transform;
			bool		Enable;
			//std::map<PropertyName, EngineProperty*> Properties;

			//component �����ÿ� component�� Ÿ���� �������� �ϰ�, component�� ���Ë� component�� Ÿ�Ը�ø� �ؾ��Ѵ�.
			//component �����ÿ��� �� ��ӹ��� Ŭ�������� actor�� �����ϰ� �ְ�, ���Ë��� actor�� ��������ؾ��Ѵ�.
			//component 
		};

		class DrawableComponent : public ComponentBase
		{
		public:
			virtual void Draw() = 0;
			void SetVisible(bool visible) { Visible = visible; }
			bool IsVisible() { return Visible; }
		private:
			bool		Visible;
			//DrawLayer	ComponentDrawLayer;
		};
	}
	
}