#include "pch.h"
#include "EngineInterface.h"
#include "EngineCoreBuild.h"
#include "EngineCore.h"

namespace Engine
{
	shared_ptr<EngineInterface> enginePtr_;

	void InitEngine()
	{
		enginePtr_ = std::static_pointer_cast<EngineInterface>(make_shared<EngineCore>());
	}

	void ReleaseEngine()
	{

	}
}