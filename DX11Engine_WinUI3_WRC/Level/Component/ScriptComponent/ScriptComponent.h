#pragma once

#include "DLLDefine.h"
#include "../ComponentBase/ComponentBase.h"
#include "Common/RuntimeContext.h"

namespace winrt
{
	struct hstring;
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
		//private:
		//	ScriptComponentImpl* pImpl;
			//IMPL_CLASS_PROPERTY(std::shared_ptr<DirectX::SpriteBatch>, SpriteBatch);
		};
	}
}