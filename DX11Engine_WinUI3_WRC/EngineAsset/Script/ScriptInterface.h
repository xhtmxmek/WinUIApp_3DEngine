#pragma once
//#include "EngineMinimal.h"
#include "DLLDefine.h"
namespace Script
{
	class ENGINE_API IScriptInterface
	{
	public:
		virtual void Init() = 0;
		virtual void Tick(float elaspedTime) = 0;
	};
}