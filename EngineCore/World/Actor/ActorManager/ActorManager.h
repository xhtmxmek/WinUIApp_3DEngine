#pragma once
#include "DLLDefine.h"
#include "Common/Uncopyable.h"
#include "Common/RuntimeContext.h"

namespace Engine
{
	namespace World
	{
		class Actor;		
		class ActorManager : public Uncopyable
		{
		public:

			ActorManager() : CurrentActorSizeFactor(1), ActoRHIstResized(false) {}

			ENGINE_API static ActorManager& GetInstance()
			{
				static ActorManager actor;
				return actor;
			}

			void ReleaseInstance();
			void Init();

			template<typename T>
			std::weak_ptr<T> CreateActor(const std::string& name)
			{
				CheckActoRHIstCapacity();
				auto newActor = CreateActor(T::ClassName(), name);
				std::weak_ptr<T> newActorPtr(std::static_pointer_cast<T>(newActor));
				return newActorPtr;
			}

			std::weak_ptr<Actor> GetActor(const std::string& actorName);
			std::weak_ptr<Actor> GetActor(unsigned int index);

			ENGINE_API size_t GetNumActoRHIst();

		private:						
			ENGINE_API void CheckActoRHIstCapacity();
			ENGINE_API std::shared_ptr<Actor> CreateActor(const std::string& className, const std::string& instanceName);
			//Actor* CreateActor(const std::string& className, const std::string& instanceName);			

			
			vector<string> actorNames_;
			std::unordered_map<string, std::shared_ptr<Actor>> Actors;
			const size_t	ActorsSizeUnit = 1000;
			const size_t	ActorSizeBias = 5;
			unsigned int	CurrentActorSizeFactor;
			bool			ActoRHIstResized;
		};
	}
}