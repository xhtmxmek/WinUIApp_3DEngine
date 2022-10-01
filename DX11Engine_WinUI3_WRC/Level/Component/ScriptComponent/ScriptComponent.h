#pragma once

#include "DLLDefine.h"
#include "../ComponentBase/ComponentBase.h"
#include "Common/RuntimeContext.h"

namespace winrt
{
	struct hstring;
}

namespace Script
{
	class IScriptInterface;
}

namespace Engine
{	
	namespace Component
	{
		class ScriptComponentImpl;
		class ENGINE_API ScriptComponent : public ComponentBase
		{
		public:
			RUNTIME_SUBCLASS(DrawableComponent)
		public:
			ScriptComponent(const std::string& name = "ScriptComponent");
			~ScriptComponent();
			void Init() final;
			void Tick(float elasedTime) final;
			//void SetInitFunc(const std::function<void()>& initFunc);
			//void SetUpdateFunc(const std::function<void(float elapsedTime)>& updateFunc);
			void SetScriptInterface(Script::IScriptInterface* scriptInterface) { ScriptInterface = scriptInterface; }
		private:
			ScriptComponentImpl* pImpl;
			Script::IScriptInterface* ScriptInterface;
		};
	}
}