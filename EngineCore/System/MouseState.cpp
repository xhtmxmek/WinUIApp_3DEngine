#include "pch.h"
#include "MouseState.h"
#include <Input/PointerButton.h>

namespace Engine
{
	namespace Input
	{
		MouseState::MouseState()
		{
			unsigned int stateCount = static_cast<unsigned int>(SharedTypes::PointerButton::Button_Max);
			state_.reserve(stateCount);
			state_.resize(stateCount);
		}
		void MouseState::SetState(vector<bool> const& pointerState)
		{
			for (int button = 0; button < pointerState.size(); button++)
			{
				state_[static_cast<unsigned int>(button)] = pointerState[button];				
			}
		}

		bool MouseState::GetState(SharedTypes::PointerButton key)
		{
			return state_[static_cast<unsigned int>(key)];
		}
	}
}

