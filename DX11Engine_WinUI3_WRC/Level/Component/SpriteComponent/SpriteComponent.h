#pragma once
#include "DLLDefine.h"
#include "../ComponentBase/ComponentBase.h"
#include "Common/RuntimeContext.h"
#include <assimp/scene.h>

namespace Engine
{
	namespace EngineAsset
	{
		class Texture;
	}

	namespace Component
	{
		class SpriteComponentImpl;
		class ENGINE_API SpriteComponent : public DrawableComponent
		{			
		public:			
			RUNTIME_SUBCLASS(DrawableComponent)
		public:
			SpriteComponent(const std::string& name = "SpriteComponent");
			~SpriteComponent() = default;
			void Init() final;			
			void Tick(float elasedTime) final;
			void Draw() final;			
		private:
			FVector2D ScreenPos;			
			//float Rotation;
			//float Scale;

			//Vector2 UVOffset;
			//Color TintColor;			
			SharedPointer<EngineAsset::Texture> BasicTexture;
			//Colors::WH
			UniquePointer<DirectX::SpriteBatch> SpriteBatch;
			UniquePointer<DirectX::BasicEffect> Effect;
		};
	}
}