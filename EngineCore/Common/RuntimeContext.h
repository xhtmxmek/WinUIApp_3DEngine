#pragma once
#include <map>
#include <string>
#include "DLLDefine.h"

namespace Engine
{
	typedef void* (*ConstructorCallBack)(const std::string& name);

	struct RuntimeClass
	{
		ConstructorCallBack constructor;
		std::string className;
	};

	class RuntimeContext
	{
	public:
		//static RuntimeContext& GetInstance()
		//{
		//	static RuntimeContext instance;
		//	return instance;
		//}
		static void InitialzeRuntimeTable();

		~RuntimeContext()
		{
			for (auto& iter : RuntimeClassTable)
			{
				delete iter.second;
			}
			RuntimeClassTable.clear();
		}
		//지금은 생성자만와 이름만 받고, 추후 부모클래스등 다양하게
		static void Regist(const std::string& className, ConstructorCallBack constructor)
		{
			RuntimeClass* metaClass = new RuntimeClass;
			metaClass->constructor = constructor;
			metaClass->className = className;
			RuntimeClassTable[className] = metaClass;
		}

		static void* New(const std::string& className, const std::string& instanceName)
		{
			auto iter = RuntimeClassTable.find(className);
			if (iter == RuntimeClassTable.end())
				return nullptr;

			ConstructorCallBack contructor = iter->second->constructor;
			return contructor(instanceName);
		}

	private:
		//RuntimeContext() {};
		static std::map<std::string, RuntimeClass*> RuntimeClassTable;
	};
}

//#define RUNTIME_ABSTRACT_ROOT_CLASS(classtype) \
//	public:\
//		static const std::string ClassName(){ return std::string(#classtype); }\
//		virtual bool KindOf(const std::string& className) { if (ClassName() == classtype) return true; }
//
//#define RUNTIME_ABSTRACT_SUB_CLASS(classtype, parent) \
//	public:\
//		static const std::string ClassName(){ return std::string(#classtype); }\
//		virtual bool KindOf(const std::string& className) { if (ClassName() == classtype) return true; return parent::KindOf(classtype); }


#define RUNTIME_ABSTRACT() \
private:\
	std::string implClassName_; \
public:\
	void ImplClassName(const std::string& name) \
	{ \
		implClassName_ = name; \
	}\
	ENGINE_API const std::string& ImplClassName() \
	{\
		return implClassName_;\
	}\

#define RUNTIME_SUBCLASS(parent)\
	private: \
		static void *Constructor(const std::string& name); \
	protected: \
	public: \
		static void RegisterRuntime();\
		ENGINE_API static const std::string& ClassName();		
		//virtual bool KindOf(const std::string& className) { if (ClassName() == classtype) return true; return parent::KindOf(classtype); }
//virtual bool KindOf(Internstring classtype) { if (ClassName() == classtype) return true; return parent::KindOf(classtype); }
/*int ClassDepth() { return parent::ClassDepth() + 1; } \*/
/*static void UnregisterRuntime();  \*/
//virtual Internstring LeafClassName(); 

#define RUNTIME_CLASS_IMPL(classtype) \
	std::string runtimeName##classtype(#classtype); \
	void *classtype::Constructor(const std::string& name) \
	{ \
		return new classtype(name);  \
	}\
	void classtype::RegisterRuntime() \
	{\
		RuntimeContext::Regist(runtimeName##classtype, classtype::Constructor); \
	}\
	const std::string& classtype::ClassName() \
	{\
		return runtimeName##classtype;\
	}\
/*RuntimeClass::GetRuntimeContext()->Register(runtimeName##classtype, classtype::Constructor, classtype::ObjectKindOf, Dictionary::group); \*/
/*
	Internstring runtimeName##classtype(#classtype); \
	Internstring classtype::ClassName() \
	{\
		return runtimeName##classtype;  \
	}\
*/
/*
	void classtype::UnregisterRuntime()\
	{\
		RuntimeClass::GetRuntimeContext()->Unregister( runtimeName##classtype ); \
	}\
	Internstring classtype::LeafClassName()\
	{\
		return ClassName(); \
	}\
*/


#define REGISTER_RUNTIME_CLASS(classType) classType::RegisterRuntime();




