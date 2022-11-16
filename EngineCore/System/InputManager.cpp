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

		void InputManager::GetMouseState(SharedTypes::PointerButton button)
		{
		}

		void InputManager::SetMouseState(vector<bool> const& pointerState, float delta, Vector2i pos)
		{			
			Mouse->SetState(pointerState, delta, pos);
		}
	}
}
