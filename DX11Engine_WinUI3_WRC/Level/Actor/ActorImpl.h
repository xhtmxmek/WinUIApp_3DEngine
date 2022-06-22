#pragma once
#include "DLLDefine.h"
#include "PropertyActor.h"

namespace Engine
{

	namespace Component
	{
		class ComponentBase;
		enum class ActorComponentType;		
		//class TransformGroup;
	}

	namespace Level
	{
		/*	인터페이스로 구현할경우에는 Actor를 상속받는 모든 클래스 안에서 Update, Render 동작을 다시 정의해야함. 어차피 정의해야하는데? 각 객체 마다 다름
			문제는 속성값에 접근할때 인터페이스를 상속받은 모든 클래스에서 해당 속성값에 대해 정의해줘야함. enable이나 visible은 공통된거기 떄문에 다시 정의할 필요가없음.
			속성값처럼 공통적으로 위에서 들고 있는 녀석이 없을때만 인터페이스를 정의해주자.
			결론적으로 Actor는 handle 클래스
			모든 actor는 DrawAble이라고 가정하기.
		*/
		class World;

		class ActorImpl
		{
		public:
			ActorImpl(const std::string& name, World* rootWorld) :Name(name), RootComponent(nullptr), RootWorld(rootWorld) {};
			
			std::shared_ptr<Component::ComponentBase> GetActorComponentByName(const std::string& name)
			{
				auto iter = Components.find(name);
				if (iter != Components.end())
					return iter->second;

				return nullptr;
			}

			void SetRootComponent(Component::ComponentBase* component)
			{
				RootComponent = component;				
			}
			
			std::shared_ptr<Component::ComponentBase> CreateComponent(const std::string& className, const std::string& instanceName);

			World* GetWorld();

			//Properties
			//bool IsEnable() const { return m_PropActor.Enable; }
			//void SetEnable(bool enable) { m_PropActor.Enable = enable; }
			//bool IsVisible() const { return m_PropActor.Visible; }
			//void SetVisible(bool visible) { m_PropActor.Visible = visible; }
			//UINT GetLayerMask() const { return m_PropActor.LayerMask; }
			//void SetLayerMask(UINT layerMask) { m_PropActor.LayerMask = layerMask; }
			//TransformGroup const& GetTransform();

		private:
			//PropertyGroup::PropertyActor m_PropActor;
			//1. 예약된 인덱스로 들어간다.(벡터의 capacity 낭비가 생김)
			//2. 맵으로 찾아오게 함(검색시간의 불편함. 근데 컴포넌트 갯수는 많은일이 없어서 이게 맞을거같음)

			World* RootWorld;
			//루트 컴포넌트 : 액터를 대표하는 컴포넌트. 컴포넌트 리스트중에 하나를 가리킴
			Component::ComponentBase* RootComponent;
			//컴포넌트 리스트 : 액터가 가지고 있는 컴포넌트 리스트. 
			std::map<std::string, std::shared_ptr<Component::ComponentBase>> Components;
			std::string Name;
			//Actor의 component의 Value가 변경되면 delegate로 연결된 함수가 호출됨
			//Actor는 기본적으로 Actor컴포넌트를 가지고 있음
			//모든 액터는 drawable이다. 에디터상에서 액터를 나타내려면 sprite를 통해서 나타내기떄문. 게임 모드에서는 visible이 false가 되는 액터들이 있고 아닌 액터들이 있다.
		};
	}
}
