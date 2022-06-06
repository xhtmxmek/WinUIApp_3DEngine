#pragma once
#include "DLLDefine.h"
namespace Engine
{
	class ENGINE_API Uncopyable
	{
	protected:
		Uncopyable(){}
		~Uncopyable(){}
	private:
		Uncopyable(const Uncopyable&);
		Uncopyable& operator=(const Uncopyable&);
	};
}