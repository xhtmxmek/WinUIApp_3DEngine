#pragma once
#include "DLLDefine.h"
#include "../ComponentBase.h"
#include "Common/RuntimeContext.h"

namespace Engine
{
	namespace Component
	{
		class SpriteComponentImpl;
		class ENGINE_API SpriteComponent : public DrawableComponent
		{			
		public:			
			RUNTIME_SUBCLASS(DrawableComponent)
		public:
			SpriteComponent(const std::string& name = "SpriteComponent");
			~SpriteComponent();
			void Init() final;			
			void Tick(float elasedTime) final;
			void Draw() final;
		private:
			SpriteComponentImpl* pImpl;
		};
	}
}