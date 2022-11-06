#pragma once
#include "System/KeyboardState.h"
#include "System/MouseState.h"

namespace SharedTypes
{
	enum class VirtualKey;
	enum class PointerButton;
}

namespace Engine
{
	namespace Input
	{
		class KeyboardState;
		class MouseState;

		class InputManager
		{
		public:
			static InputManager& GetInstance()
			{
				static InputManager inputManager;
				return inputManager;
			}

			void Initialize();
			bool GetKeyboardState(SharedTypes::VirtualKey key);
			void SetKeyboardState(SharedTypes::VirtualKey key, bool isPressed);
			void GetMouseState(SharedTypes::PointerButton button);
			void SetMouseState(SharedTypes::PointerButton button, bool isPressed, float delta, Vector2i pos);

		private:
			unique_ptr<KeyboardState> Keyboard;
			unique_ptr<MouseState> Mouse;
			InputManager() = default;
		};
	}
}
