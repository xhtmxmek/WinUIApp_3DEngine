#pragma once
#include "DLLDefine.h"

namespace Engine
{
	namespace Type
	{		
		class StringImpl
		{
		public:
			StringImpl() = default;

			std::string Data;

		};

		class ENGINE_API String
		{
		public:
			String()
			{
				pImpl = new StringImpl();
			}

			~String()
			{
				delete pImpl;
			}

			String(const String& src)
				:String()
			{
				pImpl->Data = src.pImpl->Data;
			}

			String(const std::string& src)
				:String()
			{
				pImpl->Data = src;
			}

			void operator=(const String& src) { pImpl->Data = src.pImpl->Data; }
			void operator=(const std::string& src) { pImpl->Data = src; }			
			const std::string& operator()() const { return pImpl->Data; }
			//std::string& operator() { return pImpl->Data; }

		private:
			StringImpl* pImpl;
		};

		class WStringImpl
		{
		public:
			WStringImpl() = default;

			std::wstring Data;

		};

		class ENGINE_API WString
		{
		public:
			WString()
			{
				pImpl = new WStringImpl();
			}

			~WString()
			{
				delete pImpl;
			}

			WString(const WString& src)
				:WString()
			{
				pImpl->Data = src.pImpl->Data;
			}

			WString(const std::wstring& src)
				:WString()
			{
				pImpl->Data = src;
			}

			void operator=(const WString& src) { pImpl->Data = src.pImpl->Data; }
			void operator=(const std::wstring& src) { pImpl->Data = src; }

		private:
			WStringImpl* pImpl;
		};
	}
}
