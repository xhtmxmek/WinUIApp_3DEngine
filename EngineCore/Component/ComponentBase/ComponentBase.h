#pragma once
#include "DLLDefine.h"
#include "Common/RuntimeContext.h"
#include "Common/Math/TransformGroup.h"
#include "../ComponentTypes.h"

namespace Engine
{
	namespace World
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
		class PropertyBase;

		class ComponentBase
		{
		public:
			RUNTIME_ABSTRACT()
		public:
			ENGINE_API ComponentBase(const std::string& name, SceneComponentType type);
			ENGINE_API virtual ~ComponentBase();
			virtual void Init() = 0;
			virtual void Tick(float elasedTime) = 0;

			ENGINE_API void SetPosition(Vector3f const& pos);
			ENGINE_API void SetScale(Vector3f const& scale);
			ENGINE_API void SetRotation(Vector3f const& rot);
			ENGINE_API const Vector3f GetRotation();
			ENGINE_API Math::TransformGroup& GetComponentTransform();
			ENGINE_API void UpdateComponentTransform(const Math::TransformGroup* parent = nullptr);

			ENGINE_API SceneComponentType ComponentType();

			ENGINE_API weak_ptr<ComponentBase> GetParent() 
			{ 
				return parent_; 
			}
			ENGINE_API list<shared_ptr<ComponentBase>>& GetChildren() 
			{ 
				return children_; 
			}
			ENGINE_API const string& Name() 
			{ 
				return name_; 
			}

			ENGINE_API PropertyBase* GetProperty(unsigned int index)
			{
				if ((size_t)index >= properties_.size())
					return nullptr;

				return properties_[index];
			}

			ENGINE_API const size_t NumProperty()
			{
				return properties_.size();
			}

			virtual void PostInitialize() = 0;
		protected:
			void AddProperty(PropertyBase* newProperty);
			weak_ptr<World::Actor> owner_;
			string typeName_;
		private:			
			string name_;
			weak_ptr<Component::ComponentBase> parent_;
			list<shared_ptr<ComponentBase>> children_;
			Math::TransformGroup transform_;
			bool enable_;
			SceneComponentType type_;
			vector<PropertyBase*> properties_;

		};

		class DrawableComponent : public ComponentBase
		{
		public:
			//RUNTIME_ABSTRACT_SUB_CLASS(DrawableComponent, ComponentBase)
			ENGINE_API DrawableComponent(const std::string& name);
			//DrawableComponent(const std::string& name);
			ENGINE_API void SetVisible(bool visible) { visible_ = visible; }
			ENGINE_API bool IsVisible() { return visible_.Value(); }
			virtual void AddPrimitiveToScene() = 0;
		private:			
			PropertyBool visible_;
			//DrawLayer	ComponentDrawLayer;
		};
	}	
}