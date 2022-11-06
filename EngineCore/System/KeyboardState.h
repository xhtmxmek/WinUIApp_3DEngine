#pragma once

namespace SharedTypes
{
    enum class VirtualKey;
}
namespace Engine
{
    namespace Input
    {
        class KeyboardState
        {        
        public:
            KeyboardState();
            void SetState(SharedTypes::VirtualKey key, bool isPressed);
            bool GetState(SharedTypes::VirtualKey key);
        private:
            std::vector<bool> State;            
        };
    }
}