#pragma once

namespace Engine
{
	namespace Component
	{
		//World�� ���� ����ϴ� SceneComponentŸ��. ���Ϳ��� ������Ʈ �����ÿ� ���忡 Ǫ�õǴ� ������Ʈ���� Ÿ���̴�.
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
