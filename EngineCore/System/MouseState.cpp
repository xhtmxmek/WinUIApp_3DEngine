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
		void MouseState::SetState(SharedTypes::PointerButton button, bool isPressed, float delta, Vector2i pos)
		{			
			state_[static_cast<unsigned int>(button)].isPressed_ = isPressed;
			state_[static_cast<unsigned int>(button)].delta_ = delta;
			pointerPos_ = pos;
		}

		ButtonState MouseState::GetState(SharedTypes::PointerButton key)
		{
			return state_[static_cast<unsigned int>(key)];
		}
	}
}

