#pragma once
#include "DLLDefine.h"
//#include "EngineProperty.h"

namespace DirectX	
{
	namespace SimpleMath
	{
		struct Vector3;
		struct Matrix;
	}
}

namespace Engine
{
	namespace Math
	{
		class TransformGroupImpl;

		class TransformGroup
		{
		public:
			ENGINE_API TransformGroup();
			ENGINE_API ~TransformGroup();
			ENGINE_API void SetPosition(const Vector3f& pos) { Position = pos; UpdateTransform(); }
			ENGINE_API void SetScale(const Vector3f& scale) { Scale = scale; UpdateTransform(); }
			ENGINE_API void SetRotation(const Vector3f& rotation) { Rotation = rotation; UpdateTransform(); }

			ENGINE_API const Vector3f& GetPosition() const { return Position; }
			ENGINE_API const Vector3f& GetScale() const { return Scale; }
			ENGINE_API const Vector3f& GetRotation() const { return Rotation; }

			ENGINE_API const Matrix4x4f& GetWorldMatrix() const { return WorldMatrix; }
			ENGINE_API static TransformGroup const Default() { return TransformGroup(); }
		private:
			Vector3f Position;
			Vector3f Scale;
			//	//quatÀÏ °æ¿ì 0,0,0,1
			Vector3f Rotation;

			Matrix4x4f WorldMatrix;
			Matrix4x4f LocalMatrix;

			//	//void OnChangeTransorm(EngineProperty* property);
			void UpdateTransform(TransformGroup* parent = nullptr );
			//static TransformGroup const Default();
		};
	}

	
}

