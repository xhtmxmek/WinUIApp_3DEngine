#pragma once
#include "DLLDefine.h"
#include "ComponentBase.h"
#include "Common/RuntimeContext.h"

namespace Engine
{
	namespace Component
	{
		class SpriteComponent : public DrawableComponent
		{			
		public:			
			RUNTIME_SUBCLASS(DrawableComponent)
		public:
			SpriteComponent(const std::string& name = "SpriteComponent");
			void Init() final;			
			void Tick(float elasedTime) final;
			void Draw() final;
		private:			
			std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;
		};
	}
}