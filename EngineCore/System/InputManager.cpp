#include "pch.h"
#include "InputManager.h"
#include "Input/PointerButton.h"

namespace Engine
{
	namespace Input
	{
		void InputManager::Initialize()
		{
			Keyboard = make_unique<KeyboardState>();
			Mouse = make_unique<MouseState>();
		}

		bool InputManager::GetKeyboardState(SharedTypes::VirtualKey key)
		{
			return Keyboard->GetState(key);
		}

		void InputManager::SetKeyboardState(SharedTypes::VirtualKey key, bool isPressed)
		{
			Keyboard->SetState(key, isPressed);
		}

		bool InputManager::GetMouseState(SharedTypes::PointerButton button)
		{
			return Mouse->GetState(button);
		}

		void InputManager::SetMouseState(vector<bool> const& pointerState)
		{
			Mouse->SetState(pointerState);
		}
		Vector2i& InputManager::GetMousePos()
		{
			return Mouse->GetPointerPos();
		}
		void InputManager::SetMousePos(Vector2i pos)
		{
			Mouse->SetPointerPos(pos);
		}
		Vector2i InputManager::GetMouseDelta()
		{
			return Mouse->GetPointerDelta();
		}
		int InputManager::GetWheelDelta()
		{
			return Mouse->GetWheelDelta();
		}
		void InputManager::SetWheelDelta(int wheelDelta)
		{
			Mouse->SetWheelDelta(wheelDelta);
		}
	}
}
