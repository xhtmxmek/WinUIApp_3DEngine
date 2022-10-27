#include "pch.h"
#include "InputManager.h"
#include "KeyboardState.h"

namespace Engine
{	
	namespace Input
	{
		void InputManager::Initialize()
		{
			Keyboard = make_unique<KeyboardState>();
		}

		bool InputManager::GetKeyboardState(KeyboardState::VirtualKey key)
		{	
			return Keyboard->GetState(key);
		}

		void InputManager::SetKeyboardState(KeyboardState::VirtualKey key, bool isPressed)
		{
		}

		InputManager::InputManager()
		{
			//키보드, 마우스 입력처리는 엔진에서 다루는게 맞는데, 메시지는 UI단에서 넘어옴.
			//
			//std::unique_ptr<DirectX::Keyboard> keyboard;
			//keyboard->SetWindow()
		}
	}
}
