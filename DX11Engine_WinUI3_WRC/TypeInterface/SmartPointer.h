#pragma once
#include <memory>
#include "DLLDefine.h"

namespace Engine
{
	namespace Type
	{
		template <typename T>
		class SharedPointerImpl
		{
		public:
			SharedPointerImpl() = default;

			std::shared_ptr<T> Pointer;

		};

		template <typename T>
		class ENGINE_API SharedPointer
		{
		public:
			SharedPointer()
			{
				pImpl = new SharedPointerImpl<T>;
			}

			~SharedPointer()
			{
				delete pImpl;
			}

			SharedPointer(const SharedPointer<T>& src)
				:SharedPointer()
			{
				pImpl->Pointer = src.pImpl->Pointer;
			}

			SharedPointer(const std::shared_ptr<T>& src)
				:SharedPointer()
			{
				pImpl->Pointer = src;
			}

			void operator=(const SharedPointer<T>& src) { pImpl->Pointer = src.pImpl->Pointer; }
			void operator=(const std::shared_ptr<T>& src) { pImpl->Pointer = src; }

			const std::shared_ptr<T>& operator->() { return pImpl->Pointer; }
			bool operator==(const std::shared_ptr<T>& src)
			{
				return pImpl->Pointer == src;
			}

			bool operator==(nullptr_t)
			{
				return pImpl->Pointer == nullptr;
			}

			bool operator!=(const std::shared_ptr<T>& src)
			{
				return pImpl->Pointer != src;
			}

			T* Get() { return pImpl->Pointer.get(); }

		private:
			SharedPointerImpl<T>* pImpl;
		};

		template <typename T>
		class UniquePointerImpl
		{
		public:
			UniquePointerImpl() = default;

			std::unique_ptr<T> Pointer;

		};

		template <typename T>
		class ENGINE_API UniquePointer
		{
		public:
			UniquePointer()
			{
				pImpl = new UniquePointerImpl<T>;
			}

			~UniquePointer()
			{
				delete pImpl;
			}

			UniquePointer(const UniquePointer<T>& src) = delete;
			UniquePointer(const std::unique_ptr<T>& src) = delete;
			void operator=(const UniquePointer<T>& src) = delete;
			void operator=(const std::unique_ptr<T>& src) = delete;

		private:
			UniquePointerImpl<T>* pImpl;
		};
	}
}

