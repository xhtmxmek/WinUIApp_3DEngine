#include "pch.h"
#include "RuntimeContext.h"

//Component
//#include "Level/Component/SpriteComponent/SpriteComponent.h"
#include "Component/StaticMeshComponent/StaticMeshComponent.h"
#include "Component/CameraComponent/CameraComponent.h"

//Actor
//#include "Level/Actor/SpriteActor/Sprite.h"
#include "Level/Actor/StaticMesh/StaticMesh.h"
#include "Level/Actor/DefaultActor.h"

namespace Engine
{
	using namespace Component;
	using namespace Level;

	std::map<std::string, RuntimeClass*> RuntimeContext::RuntimeClassTable;

	void RuntimeContext::InitialzeRuntimeTable()
	{				
		//component
		//REGISTER_RUNTIME_CLASS(SpriteComponent)
		REGISTER_RUNTIME_CLASS(StaticMeshComponent)
		REGISTER_RUNTIME_CLASS(CameraComponent)

		//Actor
		//REGISTER_RUNTIME_CLASS(ASprite);
		REGISTER_RUNTIME_CLASS(AStaticMesh);
		REGISTER_RUNTIME_CLASS(ADefaultActor);

	}
}
