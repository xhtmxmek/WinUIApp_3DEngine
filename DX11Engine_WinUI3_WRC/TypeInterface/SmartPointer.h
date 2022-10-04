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

			T* operator->() const { return Get(); }
			bool operator==(const std::shared_ptr<T>& src){ return pImpl->Pointer == src; }
			bool operator==(const SharedPointer<T>& src) { return pImpl->Pointer == src.pImpl->Pointer; }
			bool operator==(T* src) { return pImpl->Pointer.get() == src; }
			

			bool operator!=(const std::shared_ptr<T>& src) { return pImpl->Pointer != src; }
			bool operator!=(const SharedPointer<T>& src) { return pImpl->Pointer != src.pImpl->Pointer; }
			bool operator!=(T* src) { return pImpl->Pointer.get() != src; }

			T* Get() const { return pImpl->Pointer.get(); }

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

			UniquePointer(const UniquePointer<T>& src){ pImpl->Pointer = src.pImpl->Pointer; }
			UniquePointer(std::unique_ptr<T>& src) { pImpl->Pointer = src; }
			void operator=(const UniquePointer<T>& src) { pImpl->Pointer = src.pImpl->Pointer; }
			void operator=(std::unique_ptr<T>& src) { pImpl->Pointer = src; }

			T* operator->() const { return Get(); }
			bool operator==(const std::unique_ptr<T>& src) { return pImpl->Pointer == src; }
			bool operator==(const UniquePointer<T>& src) { return pImpl->Pointer == src.pImpl->Pointer; }
			bool operator==(T* src) { return pImpl->Pointer == src; }

			bool operator!=(const std::unique_ptr<T>& src){ return pImpl->Pointer != src; }
			bool operator!=(const UniquePointer<T>& src) { return pImpl->Pointer != src.pImpl->Pointer; }
			bool operator!=(T* src) { return pImpl->Pointer != src; }

			T* Get() const { return pImpl->Pointer.get(); }

		private:
			UniquePointerImpl<T>* pImpl;
		};
	}
}

