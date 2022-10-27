#include "pch.h"
#include "KeyboardState.h"

namespace Engine
{
	namespace Input
	{
		KeyboardState::KeyboardState()
		{
			unsigned int stateCount = static_cast<unsigned int>(VirtualKey::VirtualKey_Max);
			State.reserve(stateCount);
			State.resize(stateCount, false);
		}

		void KeyboardState::SetState(VirtualKey key, bool isPressed)
		{
			unsigned int index = static_cast<unsigned int>(key);
			State[index] = isPressed;
		}

		bool KeyboardState::GetState(VirtualKey key)
		{
			unsigned int index = static_cast<unsigned int>(key);
			return State[index];			
		}
	}
}
