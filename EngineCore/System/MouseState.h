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

            void SetPointerPos(Vector2i pos)
            {
                pointerPos_ = pos;
                lastPos_ = pos;
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

            Vector2i GetPointerDelta()
            {
                return lastPos_ - pointerPos_;
            }

        private:
            std::vector<bool> state_;
            Vector2i pointerPos_;
            Vector2i lastPos_;
            int wheelDelta_;
        };
    }
}
