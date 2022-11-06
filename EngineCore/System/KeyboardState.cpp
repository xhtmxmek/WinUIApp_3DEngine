#include "pch.h"
#include "KeyboardState.h"
#include <Input/VirtualKey.h>

namespace Engine
{
	namespace Input
	{
		KeyboardState::KeyboardState()
		{
			unsigned int stateCount = static_cast<unsigned int>(SharedTypes::VirtualKey::VirtualKey_Max);
			State.reserve(stateCount);
			State.resize(stateCount, false);
		}

		void KeyboardState::SetState(SharedTypes::VirtualKey key, bool isPressed)
		{
			unsigned int index = static_cast<unsigned int>(key);
			State[index] = isPressed;
		}

		bool KeyboardState::GetState(SharedTypes::VirtualKey key)
		{
			unsigned int index = static_cast<unsigned int>(key);
			return State[index];			
		}
	}
}
