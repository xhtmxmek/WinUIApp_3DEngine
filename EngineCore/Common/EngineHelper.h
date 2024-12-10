#pragma once

#include <ppltasks.h>
//#include "winrt/Windows.Storage.Streams.h"

namespace Engine
{
	inline float ConvertDipsToPixels(float dips, float dpi)
	{
		static const float dipsPerInch = 96.0f;
		return floorf(dips * dpi / dipsPerInch + 0.5f); // ���� ������ ������ �ݿø��մϴ�.
	}

	namespace Renderer
	{
		namespace RHI
		{
		}
	}

	
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




