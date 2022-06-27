#pragma once

//UI 관련 -> WinUI 헤더
#include <unknwn.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Microsoft.UI.Xaml.Markup.h>
#include <winrt/Microsoft.UI.Xaml.Navigation.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <Microsoft.UI.xaml.media.dxinterop.h>

//UWP 시절 winRT 헤더.. 필요없는것들은 제해도 될듯
#include "winrt/Windows.ApplicationModel.Activation.h"
#include "winrt/Windows.System.Threading.Core.h"

//Dx 관련 헤더
//comPtr 관련
#include <wrl/client.h>
//#include <wil/cppwinrt.h>
//#include <wil/cppwinrt_wrl.h>
#include <wil/com.h>

//DXToolKit
#include <d3d11_4.h>
#include <dxgi1_6.h>
#include <d2d1_3.h>
#include <d2d1effects_2.h>
#include <dwrite_3.h>

#include <pix.h>

#ifdef _DEBUG
#include <dxgidebug.h>
#endif

#include <DirectXMath.h>
#include <DirectXColors.h>

#include "BufferHelpers.h"
#include "CommonStates.h"
#include "DDSTextureLoader.h"
#include "DirectXHelpers.h"
#include "Effects.h"
#include "GamePad.h"
#include "GeometricPrimitive.h"
#include "GraphicsMemory.h"
#include "Keyboard.h"
#include "Model.h"
#include "Mouse.h"
#include "PostProcess.h"
#include "PrimitiveBatch.h"
#include "ScreenGrab.h"
#include "SimpleMath.h"
#include "SpriteBatch.h"
#include "SpriteFont.h"
#include "VertexTypes.h"
#include "WICTextureLoader.h"

//Storage 관련 
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.Storage.FileProperties.h>
#include <winrt/Windows.Storage.AccessCache.h>


//Common
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cwchar>
#include <exception>
#include <future>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <concrt.h>
#include <wincodec.h>

using namespace DirectX::SimpleMath;





