// pch.h: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#define NOMINMAX

#include "framework.h"

//UI -> WinUI
//#include <unknwn.h>
//#include <winrt/Windows.Foundation.h>
//#include <winrt/Windows.Foundation.Collections.h>
//#include <winrt/Microsoft.UI.Composition.h>
//#include <winrt/Microsoft.UI.Xaml.h>
//#include <winrt/Microsoft.UI.Xaml.Controls.h>
//#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
//#include <winrt/Microsoft.UI.Xaml.Data.h>
//#include <winrt/Microsoft.UI.Xaml.Markup.h>
//#include <winrt/Microsoft.UI.Xaml.Navigation.h>
//#include <winrt/Microsoft.UI.Dispatching.h>
//#include <Microsoft.UI.xaml.media.dxinterop.h>
//

//#include "winrt/Windows.ApplicationModel.Activation.h"
//#include "winrt/Windows.System.Threading.Core.h"

//Dx 
//comPtr
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
#include <d3d11shader.h>

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

////Storage 
//#include <winrt/Windows.Storage.h>
//#include <winrt/Windows.Storage.Pickers.h>
//#include <winrt/Windows.Storage.FileProperties.h>
//#include <winrt/Windows.Storage.AccessCache.h>

#include <assimp\scene.h>

#include "Common/EngineBaseHeader.h"

#include "Common/EngineCommonHeader.h"

using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;







#endif //PCH_H
