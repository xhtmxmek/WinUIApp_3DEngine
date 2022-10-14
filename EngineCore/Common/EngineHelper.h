#pragma once

#include <ppltasks.h>	// create_task�� ���
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
				// �� �ٿ� Win32 API ������ catch�ϱ� ���� �ߴ����� �����մϴ�.
				throw com_exception(hr);
			}
		}

		// ���� ���Ͽ��� �񵿱������� �д� �Լ��Դϴ�.
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

		// DIP(����̽� ������ �ȼ�) ���̸� ������ �ȼ� ���̷� ��ȯ�մϴ�.
		inline float ConvertDipsToPixels(float dips, float dpi)
		{
			static const float dipsPerInch = 96.0f;
			return floorf(dips * dpi / dipsPerInch + 0.5f); // ���� ������ ������ �ݿø��մϴ�.
		}

#if defined(_DEBUG)
		// SDK ���̾� ������ Ȯ���ϼ���.
		inline bool SdkLayersAvailable()
		{
			HRESULT hr = D3D11CreateDevice(
				nullptr,
				D3D_DRIVER_TYPE_NULL,       // ���� �ϵ���� ����̽��� ���� �ʿ䰡 �����ϴ�.
				0,
				D3D11_CREATE_DEVICE_DEBUG,  // SDK ���̾ Ȯ���ϼ���.
				nullptr,                    // ��� ��� ������ ����˴ϴ�.
				0,
				D3D11_SDK_VERSION,          // Microsoft Store ���� ��� �׻� �� ���� D3D11_SDK_VERSION���� �����մϴ�.
				nullptr,                    // D3D ����̽� ������ ������ �ʿ䰡 �����ϴ�.
				nullptr,                    // ��� ������ �� �ʿ䰡 �����ϴ�.
				nullptr                     // D3D ����̽� ���ؽ�Ʈ ������ ������ �ʿ䰡 �����ϴ�.
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




