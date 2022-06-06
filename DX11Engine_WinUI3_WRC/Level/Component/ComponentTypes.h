#pragma once

namespace Engine
{
	namespace Component
	{
		enum class ActorComponentType
		{			
			StaticMesh,			
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
