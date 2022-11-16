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
		void MouseState::SetState(vector<bool> const& pointerState, float delta, Vector2i pos)
		{			
			for (int button = 0; button < pointerState.size(); button++)
			{
				state_[static_cast<unsigned int>(button)].isPressed_ = pointerState[button];
				state_[static_cast<unsigned int>(button)].delta_ = delta;
			}
			pointerPos_ = pos;
			//클릭과 pos는 분리하는게 좋지않나 싶다. pos가 자주 호출될텐데..
		}

		ButtonState MouseState::GetState(SharedTypes::PointerButton key)
		{
			return state_[static_cast<unsigned int>(key)];
		}
	}
}

