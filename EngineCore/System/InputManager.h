#pragma once

namespace Engine
{
	namespace Input
	{
		class KeyboardState;
		enum class VirtualKey;

		class InputManager
		{
		public:
			static InputManager& GetInstance()
			{
				static InputManager inputManager;
				return inputManager;
			}

			void Initialize();
			bool GetKeyboardState(VirtualKey key);
			void SetKeyboardState(VirtualKey key, bool isPressed);
		private:
			unique_ptr<KeyboardState> Keyboard;
			InputManager();
		};
	}
}
