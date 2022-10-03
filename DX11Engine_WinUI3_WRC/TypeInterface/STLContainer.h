#pragma once
#include "DLLDefine.h"

namespace Engine
{
	namespace Type
	{
		/////////연관 컨테이너
		template <typename key, typename value>
		class MapImpl
		{
		public:
			MapImpl() = default;

			std::map<key, value> MapData;

		};

		template <typename key, typename value>
		class ENGINE_API Map
		{
		public:
			Map()
			{
				pImpl = new MapImpl<key, value>;
			}

			~Map()
			{
				delete pImpl;
			}

			Map(const Map<key, value>& src)
				:Map()
			{
				pImpl->MapData = src.pImpl->MapData;
			}

			Map(const std::map<key, value>& src)
				:Map()
			{
				pImpl->MapData = src;
			}

			void operator=(const Map<key, value>& src) { pImpl->MapData = src.pImpl->MapData; }
			void operator=(const std::map<key, value>& src) { pImpl->MapData = src; }

			const std::map<key, value>& GetMapData() { return pImpl->MapData; }
			

		private:
			MapImpl<key, value>* pImpl;
		};

		template <typename key>
		class SetImpl
		{
		public:
			SetImpl() = default;

			std::set<key> SetData;

		};

		template <typename key>
		class ENGINE_API Set
		{
		public:
			Set()
			{
				pImpl = new SetImpl<key>;
			}

			~Set()
			{
				delete pImpl;
			}

			Set(const Set<key>& src)
				:Set()
			{
				pImpl->SetData = src.pImpl->SetData;
			}

			Set(const std::set<key>& src)
				:Set()
			{
				pImpl->SetData = src;
			}

			void operator=(const Set<key>& src) { pImpl->SetData = src.pImpl->SetData; }
			void operator=(const std::set<key>& src) { pImpl->SetData = src; }

		private:
			SetImpl<key>* pImpl;
		};

		///////////////////////////
		
		//hash container
		template <typename key, typename value>
		class HashMapImpl
		{
		public:
			HashMapImpl() = default;

			std::unordered_map<key, value> HashMapData;

		};

		template <typename key, typename value>
		class ENGINE_API HashMap
		{
		public:
			HashMap()
			{
				pImpl = new HashMapImpl<key, value>;
			}

			~HashMap()
			{
				delete pImpl;
			}

			HashMap(const HashMap<key, value>& src)
				:Map()
			{
				pImpl->HashMapData = src.pImpl->HashMapData;
			}

			HashMap(const std::unordered_map<key, value>& src)
				:Map()
			{
				pImpl->HashMapData = src;
			}

			void operator=(const HashMap<key, value>& src) { pImpl->HashMapData = src.pImpl->HashMapData; }
			void operator=(const std::unordered_map<key, value>& src) { pImpl->HashMapData = src; }

		private:
			HashMapImpl<key, value>* pImpl;
		};

		template <typename key>
		class HashSetImpl
		{
		public:
			HashSetImpl() = default;

			std::unordered_set<key> HashSetData;

		};

		template <typename key>
		class ENGINE_API HashSet
		{
		public:
			HashSet()
			{
				pImpl = new HashSetImpl<key>;
			}

			~HashSet()
			{
				delete pImpl;
			}

			HashSet(const HashSet<key>& src)
				:HashSet()
			{
				pImpl->HashSetData = src.pImpl->HashSetData;
			}

			HashSet(const std::unordered_set<key>& src)
				:HashSet()
			{
				pImpl->HashSetData = src;
			}

			void operator=(const HashSet<key>& src) { pImpl->HashSetData = src.pImpl->HashSetData; }
			void operator=(const std::unordered_set<key>& src) { pImpl->HashSetData = src; }

		private:
			HashSetImpl<key>* pImpl;
		};

		//////////////////////sequence container///
		//vector
		template <typename T>
		class VectorImpl
		{
		public:
			VectorImpl() = default;

			std::vector<T> VectorData;

		};

		template <typename T>
		class ENGINE_API Vector
		{
		public:
			Vector()
			{
				pImpl = new VectorImpl<T>;
			}

			~Vector()
			{
				delete pImpl;
			}

			Vector(const Vector<T>& src)
				:Vector()
			{
				pImpl->VectorData = src.pImpl->VectorData;
			}

			Vector(const std::vector<T>& src)
				:Vector()
			{
				pImpl->VectorData = src;
			}

			void operator=(const Vector<T>& src) { pImpl->VectorData = src.pImpl->VectorData; }
			void operator=(const std::vector<T>& src) { pImpl->VectorData = src; }

		private:
			VectorImpl<T>* pImpl;
		};

		//list
		template <typename T>
		class ListImpl
		{
		public:
			ListImpl() = default;

			std::list<T> ListData;

		};

		template <typename T>
		class ENGINE_API List
		{
		public:
			List()
			{
				pImpl = new ListImpl<T>;
			}

			~List()
			{
				delete pImpl;
			}

			List(const List<T>& src)
				:List()
			{
				pImpl->ListData = src.pImpl->ListData;
			}

			List(const std::list<T>& src)
				:List()
			{
				pImpl->ListData = src;
			}

			void operator=(const List<T>& src) { pImpl->ListData = src.pImpl->ListData; }
			void operator=(const std::list<T>& src) { pImpl->ListData = src; }

			auto Begin() { return pImpl->ListData.begin(); }
			auto End() { return pImpl->ListData.end(); }

			const std::list<T>& GetListData() { return pImpl->ListData; }

		private:
			ListImpl<T>* pImpl;
		};
	}
}
