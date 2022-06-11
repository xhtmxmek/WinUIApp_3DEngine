#pragma once

namespace Engine
{
	namespace Component
	{
		//World가 직접 사용하는 SceneComponent타입. 액터에서 컴포넌트 생성시에 월드에 푸시되는 컴포넌트들의 타입이다.
		enum class SceneComponentType
		{	
			Drawable,			
			Collision,
			Camera,
			Sprite,
		};

		enum class PropertyName
		{
			Position,
			Rotation,
			Scale,
			Material,
		};

		enum class PropertyType
		{
			TypeBool,
			TypeInt,
			TypeFloat,
			TypeVector2,
			TypeVector3,
			TypeVector4,
		};

		enum class DrawLayer
		{
			Default,
			UI,
		};
	}
}
