#pragma once

namespace Engine
{
	namespace Utility
	{
		static std::string WstrToStr(const std::wstring& str)
		{
			string value;
			char strUnicode[256] = { 0, };
			WideCharToMultiByte(CP_ACP, 0, str.c_str(), -1, value.data(), -1, nullptr, nullptr);
			return value;
		}

		static std::wstring StrToWstr(const std::string& str)
		{
			wstring value;
			wchar_t strUnicode[256] = { 0, };
			MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, value.data(), -1);
			return value;
		}
	}
}