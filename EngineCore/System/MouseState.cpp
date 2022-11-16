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
			//Ŭ���� pos�� �и��ϴ°� �����ʳ� �ʹ�. pos�� ���� ȣ����ٵ�..
		}

		ButtonState MouseState::GetState(SharedTypes::PointerButton key)
		{
			return state_[static_cast<unsigned int>(key)];
		}
	}
}

