#pragma once
#include "DLLDefine.h"
#include "Level/Actor/Actor.h"

namespace Engine
{	
	namespace Component
	{
		class StaticMeshComponent;
	}

	namespace Level
	{
		class SpriteImpl;

		class ENGINE_API AStaticMesh : public Actor
		{
			//IMPL_CLASS_PROPERTY(std::shared_ptr<Component::SpriteComponent>, SpriteComponent)
		public:
			RUNTIME_SUBCLASS(AStaticMesh)
		public:
			//ASprite() = default;
			AStaticMesh(const std::string& actorName);
			~AStaticMesh();

			virtual void Init() final;
			virtual void Tick(float elasedTime) final;
		private:
			//Engine::Type::ISmartPointer<Component::StaticMeshComponent> Mesh;
			Type::SharedPointer<Component::StaticMeshComponent> Mesh;

		};
	}
}