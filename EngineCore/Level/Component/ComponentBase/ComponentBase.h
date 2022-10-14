#pragma once
#include "DLLDefine.h"
#include "Common/RuntimeContext.h"
#include "Common/Math/TransformGroup.h"
#include "../ComponentTypes.h"

//Component�� �̸��� �߰��Ǵ°��� �������� �ƴϱ⿡, �����ϰ��ִ� ��� ����� ����Ǵ°� ��¿�����°Ͱ���
//Component���� type�� �ʿ� ������ ���ֱ�. �ʿ��ϸ� �߰��ϱ�.
namespace Engine
{
	namespace Level
	{
		class Actor;
	}
	namespace Math
	{
		class TransformGroup;
	}

	namespace Component
	{		
		enum class SceneComponentType;		
		class DrawableComponentImpl;

		class ComponentBase
		{
		public:
			//RUNTIME_ABSTRACT_ROOT_CLASS(ComponentBase)
		public:
			ENGINE_API ComponentBase(const std::string& name, SceneComponentType type);
			ENGINE_API virtual ~ComponentBase();
			virtual void Init() = 0;
			virtual void Tick(float elasedTime) = 0;

			ENGINE_API void SetPosition(Vector3f const& pos);
			ENGINE_API void SetScale(Vector3f const& scale);
			ENGINE_API void SetRotation(Vector3f const& rot);
			ENGINE_API Vector3f GetRotation();
			ENGINE_API const Math::TransformGroup& GetComponentTransform();
			ENGINE_API void UpdateComponentTransform(const Math::TransformGroup* parent);

			ENGINE_API SceneComponentType ComponentType();

			ENGINE_API shared_ptr<ComponentBase> GetParent() { return Parent; }
			ENGINE_API list<shared_ptr<ComponentBase>>& GetChildren() { return Children; }
		protected:
			Engine::Level::Actor* Owner;
		private:			
			string Name;
			shared_ptr<Component::ComponentBase> Parent;
			list<shared_ptr<ComponentBase>> Children;
			Math::TransformGroup Transform;
			bool Enable;
			SceneComponentType Type;

		};

		class DrawableComponent : public ComponentBase
		{
		public:
			//RUNTIME_ABSTRACT_SUB_CLASS(DrawableComponent, ComponentBase)
			ENGINE_API DrawableComponent(const std::string& name) : Visible(true), ComponentBase(name, SceneComponentType::Drawable){}
			//DrawableComponent(const std::string& name);
			virtual void Draw() = 0;
			ENGINE_API void SetVisible(bool visible) { Visible = visible; }
			ENGINE_API bool IsVisible() { return Visible; }
		private:			
			bool		Visible;
			//DrawLayer	ComponentDrawLayer;
		};
	}	
}