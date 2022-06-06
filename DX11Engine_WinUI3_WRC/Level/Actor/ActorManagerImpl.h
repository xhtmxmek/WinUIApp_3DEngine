#pragma once

namespace Engine
{
	namespace Level
	{
		class Actor;

		class ActorManagerImpl
		{
		public:
			ActorManagerImpl():CurrentActorSizeFactor(1), ActorListResized(false){};
			void Init();
			void CheckActorListCapacity();
			size_t GetNumActorList();
			std::shared_ptr<Actor> CreateActor(const std::string& className, const std::string& instanceName);			
			std::shared_ptr<Actor> GetActorByName(const std::string& actorName);
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