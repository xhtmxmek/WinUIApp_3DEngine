#include "pch.h"
//#include "ComponentTypes.h"
#include "TransformGroup.h"

namespace Engine
{
	namespace Math
	{
		//const TransformGroup TransformGroup::Identity;

		TransformGroup::TransformGroup()
			:Position(0.f, 0.f, 0.f),
			Rotation(0.f, 0.f, 0.f),
			Scale(1.f, 1.f, 1.f)
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
		}
		TransformGroup::~TransformGroup()
		{
		}

		void TransformGroup::UpdateTransform(TransformGroup* parent)
		{
			
			LocalMatrix = Matrix4x4f(Scale, Quaterniont(Rotation.y, Rotation.x, Rotation.z), Position);

			if (parent)
				WorldMatrix = LocalMatrix * parent->GetWorldMatrix();
			else
				WorldMatrix = LocalMatrix;
		}

		//TransformGroup const TransformGroup::Default()
		//{
		//	// TODO: ���⿡ return ���� �����մϴ�.
		//	pImpl->Identity();
		//}

		////void TransformGroup::OnChangeTransorm(EngineProperty* property)
////{
////	UpdateTransform();
////}
	}


}