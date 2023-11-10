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
			void UpdateTransform(const TransformGroup* parent = nullptr);
			ENGINE_API void SetPosition(const Vector3f& pos) { position_ = pos; UpdateTransform(); }
			ENGINE_API void SetScale(const Vector3f& scale) { scale_ = scale; UpdateTransform(); }
			ENGINE_API void SetRotation(const Vector3f& rotation) { rotation_ = rotation; UpdateTransform(); }

			ENGINE_API const Vector3f& GetPosition();
			ENGINE_API const Vector3f& GetScale();
			ENGINE_API const Vector3f& GetRotation();

			//only editor
			ENGINE_API Component::PropertyVector3* GetPositionPtrToEditor();
			ENGINE_API Component::PropertyVector3* GetScalePtrToEditor();
			ENGINE_API Component::PropertyVector3* GetRotationPtrToEditor();

			ENGINE_API const Matrix4x4f& GetWorldMatrix() const { return worldMatrix_; }
			ENGINE_API static TransformGroup const Default() { return TransformGroup(); }

			ENGINE_API Vector3f GetFowardVector();
			ENGINE_API Vector3f GetRightVector();
			ENGINE_API Vector3f GetUpVector();
		private:
			Component::PropertyVector3 position_;
			Component::PropertyVector3 scale_;
			Component::PropertyVector3 rotation_;

			Matrix4x4f worldMatrix_;
			Matrix4x4f localMatrix_;

			Vector3f fowardVector_;
			Vector3f upvector_;
			Vector3f rightVector_;

			//	//void OnChangeTransorm(EngineProperty* property);
			//static TransformGroup const Default();
		};
	}

	
}

