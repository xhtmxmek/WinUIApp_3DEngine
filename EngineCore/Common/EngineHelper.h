#pragma once

#include <ppltasks.h>	// create_task의 경우
//#include "winrt/Windows.Storage.Streams.h"

namespace Engine
{
	namespace DX
	{
		// Helper class for COM exceptions
		class com_exception : public std::exception
		{
		public:
			com_exception(HRESULT hr) noexcept : result(hr) {}

			const char* what() const override
			{
				static char s_str[64] = {};
				sprintf_s(s_str, "Failure with HRESULT of %08X", static_cast<unsigned int>(result));
				return s_str;
			}

		private:
			HRESULT result;
		};

		inline void ThrowIfFailed(HRESULT hr)
		{
			if (FAILED(hr))
			{
				// 이 줄에 Win32 API 오류를 catch하기 위한 중단점을 설정합니다.
				throw com_exception(hr);
			}
		}

		// 이진 파일에서 비동기적으로 읽는 함수입니다.
		//inline Concurrency::task<std::vector<byte>> ReadDataAsync(const std::wstring& filename)
		//{
		//	using namespace winrt::Windows::Storage;
		//	using namespace Concurrency;

		//	auto folder = winrt::Windows::ApplicationModel::Package::Current().InstalledLocation();						
		//	return create_task(folder.GetFileAsync(winrt::param::hstring(filename.c_str()))).then([](StorageFile const& file)
		//		{
		//			return FileIO::ReadBufferAsync(file);
		//		}).then([](winrt::Windows::Storage::Streams::IBuffer const& fileBuffer) -> std::vector<byte>
		//			{
		//				std::vector<byte> returnBuffer;
		//				returnBuffer.resize(fileBuffer.Length());
		//				winrt::Windows::Storage::Streams::DataReader::FromBuffer(fileBuffer).ReadBytes(winrt::array_view<byte>(returnBuffer.data(), fileBuffer.Length()));
		//				return returnBuffer;
		//			});
		//}

		// DIP(디바이스 독립적 픽셀) 길이를 물리적 픽셀 길이로 변환합니다.
		inline float ConvertDipsToPixels(float dips, float dpi)
		{
			static const float dipsPerInch = 96.0f;
			return floorf(dips * dpi / dipsPerInch + 0.5f); // 가장 근접한 정수로 반올림합니다.
		}

#if defined(_DEBUG)
		// SDK 레이어 지원을 확인하세요.
		inline bool SdkLayersAvailable()
		{
			HRESULT hr = D3D11CreateDevice(
				nullptr,
				D3D_DRIVER_TYPE_NULL,       // 실제 하드웨어 디바이스를 만들 필요가 없습니다.
				0,
				D3D11_CREATE_DEVICE_DEBUG,  // SDK 레이어를 확인하세요.
				nullptr,                    // 모든 기능 수준이 적용됩니다.
				0,
				D3D11_SDK_VERSION,          // Microsoft Store 앱의 경우 항상 이 값을 D3D11_SDK_VERSION으로 설정합니다.
				nullptr,                    // D3D 디바이스 참조를 보관할 필요가 없습니다.
				nullptr,                    // 기능 수준을 알 필요가 없습니다.
				nullptr                     // D3D 디바이스 컨텍스트 참조를 보관할 필요가 없습니다.
			);

			return SUCCEEDED(hr);
		}
#endif

		inline DXGI_FORMAT NoSRGB(DXGI_FORMAT fmt) noexcept
		{
			switch (fmt)
			{
			case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:   return DXGI_FORMAT_R8G8B8A8_UNORM;
			case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:   return DXGI_FORMAT_B8G8R8A8_UNORM;
			case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:   return DXGI_FORMAT_B8G8R8X8_UNORM;
			default:                                return fmt;
			}
		}

	}
}




