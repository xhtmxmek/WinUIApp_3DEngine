#pragma once
#pragma comment(lib, "EngineCore.lib")

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
#include <wil/com.h>

////DXToolKit -> 엔진에 추가시킬수도 있음
#include <d3d11_4.h>
#include <dxgi1_6.h>
#include <d2d1_3.h>
#include <d2d1effects_2.h>
#include <dwrite_3.h>

#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Pickers.h>
#include <winrt/Windows.Storage.FileProperties.h>
#include <winrt/Windows.Storage.AccessCache.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>

#include <concrt.h>
#include <wincodec.h>

//std
#include <functional>

//Base Types
#include <CommonTypes.h>
#include <Math/Vector2.h>
#include <UIInfoParams.h>

#include "../EngineCore/EngineHeader_Used_Application.h"

//std 헤더들
#include <mutex>


using namespace std;
using namespace SharedTypes;





