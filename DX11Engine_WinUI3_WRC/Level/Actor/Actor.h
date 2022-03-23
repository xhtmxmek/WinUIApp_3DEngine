#pragma once
#include "PropertyActor.h"
//정의 / 구현 클래스는 일단 하나로 합쳐놓고, 참조하는곳이 많은 클래스는 정의 / 구현 나눠놓자. 근데 Actor는 여기저기서 많이 쓰일수도 있어서 나누는게 좋을지도.

namespace Engine
{
	namespace Level
	{
		/*	인터페이스로 구현할경우에는 Actor를 상속받는 모든 클래스 안에서 Update, Render 동작을 다시 정의해야함. 어차피 정의해야하는데? 각 객체 마다 다름
			문제는 속성값에 접근할때 인터페이스를 상속받은 모든 클래스에서 해당 속성값에 대해 정의해줘야함. enable이나 visible은 공통된거기 떄문에 다시 정의할 필요가없음.
			속성값처럼 공통적으로 위에서 들고 있는 녀석이 없을때만 인터페이스를 정의해주자.
			결론적으로 Actor는 handle 클래스
			모든 actor는 DrawAble이라고 가정하기. 
		*/
		class Actor
		{
		public:						
			//소멸자
			virtual ~Actor(){};

			//Draw 관련 함수
			virtual void Update(float elasedTime) = 0;
			virtual void Render() = 0;

			//Properties
			//PropActor. 필수적으로 상속시켜야할 동작들
			bool IsEnable() const { return m_PropActor.Enable; }
			void SetEnable(bool enable) { m_PropActor.Enable = enable; }
			bool IsVisible() const { return m_PropActor.Visible; }
			void SetVisible(bool visible) { m_PropActor.Visible = visible; }
			UINT GetLayerMask() const { return m_PropActor.LayerMask;  }
			void SetLayerMask(UINT layerMask) { m_PropActor.LayerMask = layerMask; }

			//TransformGroup

		private:
			PropertyGroup::PropertyActor m_PropActor;			
			//TransformGroup
		};
	}
}
