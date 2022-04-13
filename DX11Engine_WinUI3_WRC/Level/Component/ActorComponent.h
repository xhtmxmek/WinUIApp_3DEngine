#pragma once
#include "ComponentTypes.h"
#include "TransformGroup.h"

//Component�� �̸��� �߰��Ǵ°��� �������� �ƴϱ⿡, �����ϰ��ִ� ��� ����� ����Ǵ°� ��¿�����°Ͱ���
//Component���� type�� �ʿ� ������ ���ֱ�. �ʿ��ϸ� �߰��ϱ�.
namespace Engine
{
	namespace Component
	{							
		class ActorComponent
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
			std::shared_ptr<ActorComponent> Parent;
			std::list<std::shared_ptr<ActorComponent>> Child;			
			ActorComponentType ComponentType;
			TransformGroup Transform;
			bool		Enable;
			//std::map<PropertyName, EngineProperty*> Properties;
			
			//component �����ÿ� component�� Ÿ���� �������� �ϰ�, component�� ���Ë� component�� Ÿ�Ը�ø� �ؾ��Ѵ�.
			//component �����ÿ��� �� ��ӹ��� Ŭ�������� actor�� �����ϰ� �ְ�, ���Ë��� actor�� ��������ؾ��Ѵ�.
			//component 
		};

		class DrawableComponent : public ActorComponent
		{
		public:
			virtual void Draw() = 0;
			bool		Visible;
			DrawLayer	ComponentDrawLayer;
		};
	}
}