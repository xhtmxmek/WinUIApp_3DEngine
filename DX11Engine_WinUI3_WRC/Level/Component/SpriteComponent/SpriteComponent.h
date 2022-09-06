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
			void Load(const winrt::hstring& textureName);
			void SetPosition(DirectX::SimpleMath::Vector2 screenPos);
		private:
			SpriteComponentImpl* pImpl;
		};
	}
}