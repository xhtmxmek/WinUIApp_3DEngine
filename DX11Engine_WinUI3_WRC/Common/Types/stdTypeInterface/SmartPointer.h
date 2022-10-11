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
			SharedPointer() { pImpl = new SharedPointerImpl<T>; }
			~SharedPointer() { delete pImpl; }

			SharedPointer(const SharedPointer<T>& src) :SharedPointer() { pImpl->Pointer = src.pImpl->Pointer; }
			SharedPointer(const std::shared_ptr<T>& src) :SharedPointer() { pImpl->Pointer = src; }
			SharedPointer(T* src) :SharedPointer() { pImpl->Pointer.reset(src); }
			SharedPointer(nullptr_t) : SharedPointer() { pImpl->Pointer = nullptr; }

			SharedPointer<T>& operator=(const SharedPointer<T>& src) { pImpl->Pointer = src.pImpl->Pointer; return *this; }
			SharedPointer<T>& operator=(const std::shared_ptr<T>& src) { pImpl->Pointer = src; return *this; }
			SharedPointer<T>& operator=(nullptr_t) { pImpl->Pointer = nullptr; return *this; }
			SharedPointer<T>& operator=(T* src) { pImpl->Pointer = src; return *this; }

			T* operator->() const { return Get(); }
			bool operator==(const std::shared_ptr<T>& src){ return pImpl->Pointer == src; }
			bool operator==(const SharedPointer<T>& src) { return pImpl->Pointer == src.pImpl->Pointer; }
			bool operator==(T* src) { return pImpl->Pointer.get() == src; }
			bool operator==(nullptr_t) { return pImpl->Pointer == nullptr; }
			

			bool operator!=(const std::shared_ptr<T>& src) { return pImpl->Pointer != src; }
			bool operator!=(const SharedPointer<T>& src) { return pImpl->Pointer != src.pImpl->Pointer; }
			bool operator!=(T* src) { return pImpl->Pointer.get() != src; }
			bool operator!=(nullptr_t) { return pImpl->Pointer != nullptr; }
			bool operator!=(nullptr_t) const { return pImpl->Pointer != nullptr; }

			std::shared_ptr<T>& operator()() { return pImpl->Pointer; }
			std::shared_ptr<T>& operator()() const { return pImpl->Pointer; }
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
			UniquePointer() { pImpl = new UniquePointerImpl<T>; }
			~UniquePointer() { delete pImpl; }

			UniquePointer(const UniquePointer<T>& src) = delete;
			UniquePointer(std::unique_ptr<T>& src) = delete;
			UniquePointer(UniquePointer<T>&& src) { pImpl->Pointer.reset(src.pImpl->Pointer.release()); }
			UniquePointer(std::unique_ptr<T>&& src) { pImpl->Pointer.reset(src.release()); }

			UniquePointer<T>& operator=(const UniquePointer<T>& src) = delete;
			UniquePointer<T>& operator=(std::unique_ptr<T>& src) =  delete;
			UniquePointer<T>& operator=(const UniquePointer<T>&& src) { pImpl->Pointer.reset(src.pImpl->Pointer.release()); return *this; }
			UniquePointer<T>& operator=(std::unique_ptr<T>&& src) { pImpl->Pointer.reset(src.release()); return *this; }
			

			T* operator->() const { return Get(); }
			bool operator==(const std::unique_ptr<T>& src) { return pImpl->Pointer == src; }
			bool operator==(const UniquePointer<T>& src) { return pImpl->Pointer == src.pImpl->Pointer; }
			bool operator==(T* src) { return pImpl->Pointer == src; }
			bool operator==(nullptr_t) { return pImpl->Pointer == nullptr; }

			bool operator!=(const std::unique_ptr<T>& src){ return pImpl->Pointer != src; }
			bool operator!=(const UniquePointer<T>& src) { return pImpl->Pointer != src.pImpl->Pointer; }
			bool operator!=(T* src) { return pImpl->Pointer != src; }
			bool operator!=(nullptr_t) { return pImpl->Pointer != nullptr; }

			const std::unique_ptr<T>& operator()() const { return pImpl->Pointer; }
			T* Get() const { return pImpl->Pointer.get(); }

		private:
			UniquePointerImpl<T>* pImpl;
		};

		template <typename T>
		class TestClass
		{
		public:
			TestClass(){member = T};
			int member;
		};
	}
}

