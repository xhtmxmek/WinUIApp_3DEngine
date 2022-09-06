#include "EngineMinimal.h"
//#include "ComponentTypes.h"
#include "TransformGroup.h"
#include "TransformGroupImpl.h"

namespace Engine
{
	namespace Math
	{
		//const TransformGroup TransformGroup::Identity;

		TransformGroup::TransformGroup()
			//:Position(0, 0, 0),
			//Rotation(0, 0, 0),
			//Scale(1, 1, 1)

			//:Position("Position", PropertyType::TypeVector3, Vector3(0, 0, 0)),
			//Rotation("Rotation", PropertyType::TypeVector3, Vector3(0, 0, 0)),
			//Scale("Position", PropertyType::TypeVector3, Vector3(1, 1, 1))
		{
			//�������ϴ� ������ �ٱ��� Positon property�� Onchange�� �θ��� ����� callback(�̰�쿡�� 

			//property�� Onchage�� ȣ���ϸ� ��ϵ� Delegate���� ȣ��
			//OnchagedTransform�� Property�� Onchage�� bind ���Ѿߵ�

			//std::function<void(EngineProperty*)> OnChange = TransformGroup::OnChangeTransorm;			
			//Position.OnChange = std::bind(&TransformGroup::OnChangeTransorm, this, std::placeholders::_1);
			//Rotation.OnChange = std::bind(&TransformGroup::OnChangeTransorm, this, std::placeholders::_1);
			//Scale.OnChange = std::bind(&TransformGroup::OnChangeTransorm, this, std::placeholders::_1);

			//pos�� Value�� =�����ڷ� ������ onchanged �Լ� �Ҹ�.
			//onchanged&SetTransform�� UI���� property �����Ҷ��� �����			

			pImpl = new TransformGroupImpl();
		}
		TransformGroup::~TransformGroup()
		{
			delete pImpl;
		}

		void TransformGroup::SetPosition(const Vector3& pos)
		{
			pImpl->SetPosition(pos);
			//UpdateTransform();
		}
		void TransformGroup::SetScale(const Vector3& scale)
		{
			pImpl->SetScale(scale);
			//UpdateTransform();
		}
		void TransformGroup::SetRotation(const Vector3& rotation)
		{
			pImpl->SetRotation(rotation);
			//UpdateTransform();
		}

		const Vector3& TransformGroup::GetPosition() const
		{
			return pImpl->GetPosition();
		}
		const Vector3& TransformGroup::GetScale() const
		{
			return pImpl->GetScale();
		}
		const Vector3& TransformGroup::GetRotation() const
		{
			return pImpl->GetRotation();
		}
		////void TransformGroup::OnChangeTransorm(EngineProperty* property)
		////{
		////	UpdateTransform();
		////}
		//void TransformGroup::UpdateTransform(TransformGroup* parent)
		//{
		//	Local = Matrix::CreateScale(Scale) * Matrix::CreateFromYawPitchRoll(Rotation) * Matrix::CreateTranslation(Position);

		//	if (parent)
		//		World = Local * parent->GetWorld();
		//	else
		//		World = Local;
		//}
	}


}