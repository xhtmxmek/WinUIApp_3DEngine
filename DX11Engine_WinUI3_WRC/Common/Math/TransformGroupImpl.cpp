#include "EngineMinimal.h"
#include "TransformGroupImpl.h"

namespace Engine
{
	namespace Math
	{
		TransformGroupImpl::TransformGroupImpl()
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


	}
}

