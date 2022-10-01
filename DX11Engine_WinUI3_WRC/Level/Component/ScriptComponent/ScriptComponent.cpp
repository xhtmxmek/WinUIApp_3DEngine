#include "EngineMinimal.h"
#include "ScriptComponent.h"
#include "ScriptComponentImpl.h"
#include "EngineAsset/Script/ScriptInterface.h"

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
			delete pImpl;			
		}

		void ScriptComponent::Init()
		{
			//pImpl->Init();
			ScriptInterface->Init();
		}

		void ScriptComponent::Tick(float elapsedTime)
		{
			ScriptInterface->Tick(elapsedTime);
			//pImpl->Tick(elapsedTime);			
		}
		//void ScriptComponent::SetInitFunc(const std::function<void()>& initFunc)
		//{
		//	pImpl->SetInitFunc(initFunc);
		//}
		//void ScriptComponent::SetUpdateFunc(const std::function<void(float elapsedTime)>& updateFunc)
		//{
		//	pImpl->SetUpdateFunc(updateFunc);
		//}
	}
}