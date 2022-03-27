#pragma once
#include "Actor.h"
/*
액터 생성/관리용 클래스. 액터 생성요청과 렌더링은 별개의 쓰레드로 돌게하도록 바꾸는게 좋을듯
자료가 충분히 많을때는 해시 테이블이 좋음. 해시 맵으로 관리되기에 해시 충돌이 있을수 있음. 삽입/삭제가 빈번하지 않고 정렬될 필요가 있는 자료구조에만 map을 쓰자
key값은 string으로.
*/

/*enumClass를 모아서 헤더로 만들고 헤더를 각 헤더마다 포함시키면 의존성이 연쇄적으로 발생하게됨(대신 관리는 편하지만, 컴파일 타임의 의도치 않은 증가가 일어날수 있음)
enum을 쪼개서 의존성을 최대한 줄여보거나.. 그냥 클래스 내부에 선언하거나,(밖에서 쓸일이 없으면. 될수있으면 안쪽에서 쓰다가, 밖에 쓸일이 있으면 그때 모아서 만들자)
*/

/*1000개의 액터를 세팅해놓고, 1000개가 넘어가면 2000개를 세팅하는 식으로.
*/

namespace Engine
{
	namespace Level
	{
		class Actor;
		
		//액터가 변경되면 ActorManager도 빌드해야 하고 ActorManager빌드하면 이 친구를 포함하는 모든 소스파일들 다시 빌드해야함. ActorManager에서 요청하는 많은 파일들이 있을것인데...
		//근데 Actor매니저에서 Actor를 요청해서 쓰는 녀석들은 cpp에서는 어차피 Actor를 포함시켜야함. 즉 ActorManager를 직접 자료형으로 들고 있는 최상위 엔진 클래스만 다시 빌드됨.
		//Actor를 빌드, Actor 매니저를 빌드, Actor매니저를 들고 있는 엔진이 빌드.
		//Actor는 인터페이스 구성되면 빌드될일이 거의 없음. 자식들이 빌드되는 것이지.
		class ActorManager
		{			
		public:
			ActorManager();
			void Init();			

			template<typename T>
			std::shared_ptr<Actor> CreateActor(const std::string& name)
			{				
				
				//Actor가 일정 임계값 이상 만큼 생성요청이 올경우에는 Actorlist의 사이즈를 늘려준 후에 Copy한다
				if (Actors.size() % ActorsSizeUnit < (ActorsSizeUnit - ActorSizeBias))
					ActorListResized = false;
				else
				{
					if (!ActorListResized)
					{
						std::unordered_map<std::string, std::shared_ptr<Actor>> tempActors;
						tempActors.reserve(CurrentActorSizeFactor * ActorsSizeUnit);
						std::copy(Actors.begin(), Actors.end(), tempActors.begin(), tempActors.end());
						Actors.reserve(CurrentActorSizeFactor * ActorsSizeUnit);
						std::copy(tempActors.begin(), tempActors.end(), Actors.begin(), Actors.end());

						ActorListResized = true;
						CurrentActorSizeFactor++;
					}
				}				

				std::shared_ptr<T>(new T(name)) newActor;
				Actors.insert(make_pair(name, newActor));
				return newActor;
			}
		private:
			std::unordered_map<std::string, std::shared_ptr<Actor>> Actors;
			//public으로 공개해서 외부에서 사용할일이 있을것같으면 그때 변경
			const size_t	ActorsSizeUnit = 1000;
			const size_t	ActorSizeBias = 5;
			unsigned int	CurrentActorSizeFactor;
			bool			ActorListResized;
		};
	}
}