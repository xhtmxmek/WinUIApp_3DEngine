#include "EngineMinimal.h"
#include "RuntimeContext.h"
#include "Level/Component/SpriteComponent/SpriteComponent.h"
#include "Level/Component/StaticMeshComponent/StaticMeshComponent.h"
#include "Level/Component/CameraComponent/CameraComponent.h"
#include "Level/Actor/SpriteActor/Sprite.h"

namespace Engine
{
	using namespace Component;
	using namespace Level;

	std::map<std::string, RuntimeClass*> RuntimeContext::RuntimeClassTable;

	void RuntimeContext::InitialzeRuntimeTable()
	{		
		REGISTER_RUNTIME_CLASS(SpriteComponent);
		REGISTER_RUNTIME_CLASS(StaticMeshComponent);
		REGISTER_RUNTIME_CLASS(CameraComponent);

		REGISTER_RUNTIME_CLASS(ASprite);
	}
}
