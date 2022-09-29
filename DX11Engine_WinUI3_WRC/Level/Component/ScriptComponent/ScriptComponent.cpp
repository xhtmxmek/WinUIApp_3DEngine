#include "EngineMinimal.h"
#include "ScriptComponent.h"

namespace Engine
{
	namespace Component
	{
		RUNTIME_CLASS_IMPL(ScriptComponent)

		ScriptComponent::ScriptComponent(const std::string& name)			
			//:pImpl(nullptr)
			:ComponentBase(name, SceneComponentType::Script)
		{
			//pImpl = new SpriteComponentImpl(name);
			//SetDiffuseTexture()			
		}

		ScriptComponent::~ScriptComponent()
		{
			//delete pImpl;
		}

		void ScriptComponent::Init()
		{
			//pImpl->Init();
		}

		void ScriptComponent::Tick(float elasedTime)
		{
			//pImpl->Tick(elasedTime);
		}
	}
}