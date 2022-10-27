#pragma once

namespace Engine
{
	namespace Input
	{
		class KeyboardState;
		enum class KeyboardState::VirtualKey;

		class InputManager
		{
		public:
			static InputManager& GetInstance()
			{
				static InputManager inputManager;
				return inputManager;
			}

			void Initialize();
			bool GetKeyboardState(KeyboardState::VirtualKey key);
			void SetKeyboardState(KeyboardState::VirtualKey key, bool isPressed);
		private:
			unique_ptr<KeyboardState> Keyboard;
			InputManager();
		};
	}
}
