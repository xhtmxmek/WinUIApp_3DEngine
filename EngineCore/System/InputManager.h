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
			ENGINE_API bool GetKeyboardState(SharedTypes::VirtualKey key);
			void SetKeyboardState(SharedTypes::VirtualKey key, bool isPressed);
			ENGINE_API bool GetMouseState(SharedTypes::PointerButton button);
			void SetMouseState(vector<bool> const& pointerState);
			ENGINE_API Vector2i& GetMousePos();
			void SetMousePos(Vector2i pos);
			ENGINE_API Vector2i GetMouseDelta();
			ENGINE_API int GetWheelDelta();
			void SetWheelDelta(int wheelDelta);

		private:
			unique_ptr<KeyboardState> Keyboard;
			unique_ptr<MouseState> Mouse;
			InputManager() = default;
		};
	}
}
