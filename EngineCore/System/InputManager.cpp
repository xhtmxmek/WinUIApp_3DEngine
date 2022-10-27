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

		bool InputManager::GetKeyboardState(VirtualKey key)
		{	
			return Keyboard->GetState(key);
		}

		void InputManager::SetKeyboardState(VirtualKey key, bool isPressed)
		{
			Keyboard->SetState(key, isPressed);
		}

		InputManager::InputManager()
		{
			//Ű����, ���콺 �Է�ó���� �������� �ٷ�°� �´µ�, �޽����� UI�ܿ��� �Ѿ��.
			//
			//std::unique_ptr<DirectX::Keyboard> keyboard;
			//keyboard->SetWindow()
		}
	}
}
