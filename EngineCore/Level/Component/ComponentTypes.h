#pragma once

namespace Engine
{
	namespace Component
	{
		//World�� ���� ����ϴ� SceneComponentŸ��. ���Ϳ��� ������Ʈ �����ÿ� ���忡 Ǫ�õǴ� ������Ʈ���� Ÿ���̴�.
		enum class SceneComponentType
		{	
			Drawable,			
			//Collision,
			Camera,
			Sprite,
			Script,
			ComponentType_Max
		};

		enum class PropertyName
		{
			Position,
			Rotation,
			Scale,
			Material,
		};

		enum class DrawLayer
		{
			Default,
			UI,
		};
	}
}
