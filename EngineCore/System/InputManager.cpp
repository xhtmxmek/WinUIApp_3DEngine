#include "pch.h"
#include "InputManager.h"

namespace Engine
{	
	InputManager::InputManager()
	{
		winrt::
		//키보드, 마우스 입력처리는 엔진에서 다루는게 맞는데, 메시지는 UI단에서 넘어옴.
		//
		//std::unique_ptr<DirectX::Keyboard> keyboard;
		//keyboard->SetWindow()
	}
}
