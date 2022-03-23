#pragma once
/*
액터 생성/관리용 클래스. 액터 생성요청과 렌더링은 별개의 쓰레드로 돌게하도록 바꾸는게 좋을듯
자료가 충분히 많을때는 해시 테이블이 좋음. 해시 맵으로 관리되기에 해시 충돌이 있을수 있음. 삽입/삭제가 빈번하지 않고 정렬될 필요가 있는 자료구조에만 map을 쓰자
key값은 string으로.
*/

//enumClass를 모아서 헤더로 만들고 헤더를 각 헤더마다 포함시키면 의존성이 연쇄적으로 발생하게됨(대신 관리는 편하지만, 컴파일 타임의 의도치 않은 증가가 일어날수 있음)
//enum을 쪼개서 의존성을 최대한 줄여보거나.. 그냥 클래스 내부에 선언하거나,(밖에서 쓸일이 없으면)

namespace Engine
{
	namespace Level
	{
		class Actor;
		
		class ActorManager
		{			
		public:
			void Init();

			template<typename T>
			std::shared_ptr<Actor> CreateActor(const std::string& name)
			{				
				std::shared_ptr<T(name)>(new T(name)) newActor;
				Actors.insert(make_pair(name, newActor));
			}
		private:
			std::unordered_map<std::string, std::shared_ptr<Actor>> Actors;
			//public으로 공개해서 외부에서 사용할일이 있을것같으면 그때 변경
			const unsigned int ActorsSize = 1000;
		};
	}
}