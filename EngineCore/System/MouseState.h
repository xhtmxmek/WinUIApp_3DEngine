#pragma once

namespace SharedTypes
{
    enum class PointerButton;
}

namespace Engine
{
    namespace Input
    {
        class MouseState
        {
        public:
            MouseState();
            void SetState(vector<bool> const& pointerState);
            bool GetState(SharedTypes::PointerButton button);

            void SetPointerPos(SharedTypes::Vector2i pos)
            {
                pointerPos_ = pos;
            }
            Vector2i& GetPointerPos()
            {
                return pointerPos_;
            }

            void SetWheelDelta(int wheelDelta)
            {
                wheelDelta_ = wheelDelta;
            }
            int GetWheelDelta()
            {
                return wheelDelta_;
            }

        private:
            std::vector<bool> state_;
            Vector2i pointerPos_;
            int wheelDelta_;
        };
    }
}
