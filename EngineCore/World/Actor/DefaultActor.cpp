#include "pch.h"
#include "DefaultActor.h"
//#include "SpriteImpl.h"

namespace Engine
{
	namespace World
	{
		RUNTIME_CLASS_IMPL(ADefaultActor)

			ADefaultActor::ADefaultActor(const std::string& actorName)
			:Actor(actorName)
		{
		}
		ADefaultActor::~ADefaultActor()
		{
		}
		void ADefaultActor::Init()
		{
		}

		void ADefaultActor::Tick(float elapsedTime)
		{
		}
	}
}



