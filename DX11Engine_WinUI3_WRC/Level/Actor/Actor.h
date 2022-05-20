#pragma once
//ComponentType을 여기에 포함하면 component가 변경되면 actor가 변경되고 actor가 변경되면 actor를 가지고있는 헤더파일 모두가 변경됨
//enum을 포함해도 마찬가지로 이게 빌드됨.
//component와 enum을 연결하느냐 마냐인데.. 분리하는게 맞는거같다.
//#include "Component/ComponentName.h"
#include "PropertyActor.h"
//정의 / 구현 클래스는 일단 하나로 합쳐놓고, 참조하는곳이 많은 클래스는 정의 / 구현 나눠놓자. 근데 Actor는 여기저기서 많이 쓰일수도 있어서 나누는게 좋을지도.

namespace Engine
{
	namespace Component
	{
		class ComponentBase;
		enum class ActorComponentType;
		class TransformGroup;
	}

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

			virtual void Init() = 0;

			//Draw 관련 함수
			virtual void Tick(float elasedTime) = 0;			
		
			template<typename T>
			std::shared_ptr<T> GetActorComponent(Component::ActorComponentType componentType)
			{
				auto iter = Components.find(componentType);
				if (iter != Components.end())
					return static_cast<shared_ptr<T>>(iter->second);

				return nullptr;
			}

			//Properties
			//bool IsEnable() const { return m_PropActor.Enable; }
			//void SetEnable(bool enable) { m_PropActor.Enable = enable; }
			//bool IsVisible() const { return m_PropActor.Visible; }
			//void SetVisible(bool visible) { m_PropActor.Visible = visible; }
			//UINT GetLayerMask() const { return m_PropActor.LayerMask; }
			//void SetLayerMask(UINT layerMask) { m_PropActor.LayerMask = layerMask; }
			Component::TransformGroup const& GetTransform();			
			
		private:
			//PropertyGroup::PropertyActor m_PropActor;
			//1. 예약된 인덱스로 들어간다.(벡터의 capacity 낭비가 생김)
			//2. 맵으로 찾아오게 함(검색시간의 불편함. 근데 컴포넌트 갯수는 많은일이 없어서 이게 맞을거같음)
			std::shared_ptr<Component::ComponentBase> RootComponent;
			std::map<std::string, std::shared_ptr<Component::ComponentBase>> Components;
			//Actor의 component의 Value가 변경되면 delegate로 연결된 함수가 호출됨
			//Actor는 기본적으로 Actor컴포넌트를 가지고 있음
			//모든 액터는 drawable이다. 에디터상에서 액터를 나타내려면 sprite를 통해서 나타내기떄문. 게임 모드에서는 visible이 false가 되는 액터들이 있고 아닌 액터들이 있다.
		};
	}
}
