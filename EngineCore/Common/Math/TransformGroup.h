#pragma once
#include "DLLDefine.h"
#include "Component/Property/PropertyBase.h"
//#include "EngineProperty.h"

namespace DirectX	
{
	namespace SimpleMath
	{
		struct Vector3;
		struct Matrix;
	}

	namespace Component
	{
		class PropertyVector3;
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
			ENGINE_API void SetPosition(const Vector3f& pos) { position_ = pos; UpdateTransform(); }
			ENGINE_API void SetScale(const Vector3f& scale) { scale_ = scale; UpdateTransform(); }
			ENGINE_API void SetRotation(const Vector3f& rotation) { rotation_ = rotation; UpdateTransform(); }

			ENGINE_API const Vector3f& GetPosition();
			ENGINE_API const Vector3f& GetScale();
			ENGINE_API const Vector3f& GetRotation();

			ENGINE_API const Matrix4x4f& GetWorldMatrix() const { return worldMatrix_; }
			ENGINE_API static TransformGroup const Default() { return TransformGroup(); }
		private:
			Component::PropertyVector3 position_;
			Component::PropertyVector3 scale_;			
			Component::PropertyVector3 rotation_;

			Matrix4x4f worldMatrix_;
			Matrix4x4f localMatrix_;

			//	//void OnChangeTransorm(EngineProperty* property);
			void UpdateTransform(TransformGroup* parent = nullptr );
			//static TransformGroup const Default();
		};
	}

	
}

