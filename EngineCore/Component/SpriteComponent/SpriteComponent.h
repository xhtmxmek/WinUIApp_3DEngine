#pragma once
//#include "DLLDefine.h"
#include "Component/ComponentBase/ComponentBase.h"
#include "Common/RuntimeContext.h"

namespace Engine
{
	namespace EngineAsset
	{
		class Texture;
	}

	namespace Component
	{
		class SpriteComponentImpl;
		class SpriteComponent : public DrawableComponent
		{			
		public:			
			RUNTIME_SUBCLASS(DrawableComponent)
		public:
			ENGINE_API SpriteComponent(const std::string& name = "SpriteComponent");
			ENGINE_API ~SpriteComponent() = default;
			ENGINE_API void Init() final;
			void Tick(float elasedTime) final;
			void Draw() final;			
		private:
			Vector2f ScreenPos;
			//float Rotation;
			//float Scale;

			Vector2f UVOffset;
			Color4f TintColor;
			shared_ptr<EngineAsset::Texture> BasicTexture;			
			unique_ptr<DirectX::SpriteBatch> SpriteBatch;
			unique_ptr<DirectX::BasicEffect> Effect;
		};
	}
}