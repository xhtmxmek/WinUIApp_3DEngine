#pragma once

namespace SharedTypes
{
    enum class PointerButton;
}

namespace Engine
{
    namespace Input
    {
        struct ButtonState
        {
            bool isPressed_;
            float delta_;

            ButtonState():
                isPressed_(false),
                delta_(0.0f)
            {
            }
        };

        class MouseState
        {
        public:
            MouseState();
            void SetState(vector<bool> const& pointerState, float delta, Vector2i pos);
            ButtonState GetState(SharedTypes::PointerButton button);
        private:
            std::vector<ButtonState> state_;
            Vector2i pointerPos_;
        };
    }
}
