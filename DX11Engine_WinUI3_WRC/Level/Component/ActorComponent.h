#pragma once

namespace Engine
{
	namespace Component
	{
		class ActorComponent
		{
		public:
			ActorComponent();			
		private:
			ActorComponentType ComponentType;


			//component 생성시에 component의 타입을 명시해줘야 하고, component를 얻어올떄 component의 타입명시를 해야한다.
			//component 생성시에는 각 상속받은 클래스에서 actor를 포함하고 있고, 얻어올떄도 actor를 헤더포함해야한다.
			//component 
		};
	}
}