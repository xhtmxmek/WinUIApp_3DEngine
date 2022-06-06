#include "EngineMinimal.h"
#include "RuntimeContext.h"
#include "Level/Component/SpriteComponent.h"
#include "Level/Actor/Sprite.h"

namespace Engine
{
	using namespace Component;
	using namespace Level;

	std::map<std::string, RuntimeClass*> RuntimeContext::RuntimeClassTable;

	void RuntimeContext::InitialzeRuntimeTable()
	{		
		REGISTER_RUNTIME_CLASS(SpriteComponent);
		REGISTER_RUNTIME_CLASS(ASprite);
	}
}
