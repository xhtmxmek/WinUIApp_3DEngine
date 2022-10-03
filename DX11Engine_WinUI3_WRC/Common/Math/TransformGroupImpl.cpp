#include "EngineMinimal.h"
#include "TransformGroupImpl.h"

namespace Engine
{
	namespace Math
	{
		TransformGroupImpl::TransformGroupImpl()
			:Position(0.f, 0.f, 0.f),
			Rotation(0.f, 0.f, 0.f),
			Scale(1.f, 1.f, 1.f)			
		{
		}

		void TransformGroupImpl::SetPosition(const DirectX::SimpleMath::Vector3& pos)
		{
			Position = pos;
		}

		void TransformGroupImpl::SetScale(const DirectX::SimpleMath::Vector3& scale)
		{
			Scale = scale;
		}

		void TransformGroupImpl::SetRotation(const DirectX::SimpleMath::Vector3& rotation)
		{
			Rotation = rotation;
		}

		const DirectX::SimpleMath::Vector3& TransformGroupImpl::GetPosition() const
		{			
			return Position;
		}

		const DirectX::SimpleMath::Vector3& TransformGroupImpl::GetScale() const
		{
			return Scale;
		}

		const DirectX::SimpleMath::Vector3& TransformGroupImpl::GetRotation() const
		{
			return Rotation;
		}

		void TransformGroupImpl::UpdateTransform(TransformGroup* parent)
		{
			Local = Matrix::CreateScale(Scale) * Matrix::CreateFromYawPitchRoll(Rotation) * Matrix::CreateTranslation(Position);

			if (parent)
				World = Local * parent->GetWorld();
			else
				World = Local;
		}

	}
}

