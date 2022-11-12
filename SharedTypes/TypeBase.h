#pragma once
#include "pch.h"

namespace SharedTypes
{
	enum class PropertyType
	{
		TypeBool,
		TypeInt,
		TypeFloat,
		TypeVector2,
		TypeVector3,
		TypeVector4,
		TypeSelectList
	};

	class TypeBase
	{
	public:
		//OnChanged �Լ� �����͸� �־��ָ�ɵ�
		//������Ƽ�� OnChanged ȣ��Ǹ� Value�� �־��־� Callback������
		//OnChange �̺�Ʈ�� ������ �����Ű��ʹٸ�, OnChange�� ���ͷ� ����� �ش� �̺�Ʈ�� ���ε���Ű��.
		TypeBase(std::string const& name, PropertyType const& type)
			:name_(name), type_(type)
		{
		}
		std::function<void(TypeBase*)> OnChange;
		void ApplyChange() { OnChange(this); }
	private:
		std::string name_;
		PropertyType type_;
		//std::vector<EngineProperty> child�� ���߿� ����
	};

	class TypeInt : public TypeBase
	{
	public:
		TypeInt(std::string const& name, PropertyType const& type)
			:TypeBase(name, type),
			value_(0)
		{
		}
		TypeInt& operator=(int value)
		{
			value_ = value; return (*this);
		}
	private:
		int value_;
		//std::vector<EngineProperty> child�� ���߿� ����
	};

	class TypeFloat : public TypeBase
	{
	public:
		TypeFloat(std::string const& name, PropertyType const& type)
			:TypeBase(name, type),
			value_(0.0f)
		{
		}

		TypeFloat& operator=(int value)
		{
			value_ = value; return (*this);
		}
	private:
		float value_;
		//std::vector<EngineProperty> child�� ���߿� ����
	};

	class TypeBool : public TypeBase
	{
	public:
		TypeBool(std::string const& name, PropertyType const& type)
			:TypeBase(name, type),
			value_(false)
		{
		}
		TypeBool& operator=(int value)
		{
			value_ = value; return (*this);
		}

	private:
		float value_;
	};

	//Property value�� Int. enum�� ������ �ְ� UI���� key���� �ش��ϴ� String�� ������.
	class TypeEnum : public TypeInt
	{
	public:
		TypeEnum(std::string const& name, PropertyType const& type)
			:TypeInt(name, type)
		{
		}

		void Register(const std::string& name, int value)
		{
			selectList_[name] = value;
		}

		TypeEnum& operator=(int value)
		{
			(TypeInt::operator=(value));
			return *this;
		}
	private:
		std::map<std::string, int> selectList_;
	};

	//class PropertyBool : public EngineProperty
	//{
	//	//operator�� ��������� �ʿ�									
	//public:
	//	PropertyBool(std::string const& name, PropertyType const& type, const bool& src)
	//		:EngineProperty(name, type), value_(src) {}
	//	const PropertyBool& operator=(const bool& value) { Value = value; return *this; }
	//	const bool GetValue() const { return Value; }
	//};

	//class PropertyVector3 : public EngineProperty
	//{
	//public:
	//	PropertyVector3(std::string const& name, PropertyType const& type, const Vector3& src)
	//		: EngineProperty(name, type), Value(src) {}
	//	const PropertyVector3& operator=(const Vector3& value) { Value = value; return *this; }
	//	const Vector3& GetValue() const { return Value; }
	//	const Vector3& operator()() { return Value; }
	//	//const Vector3& operator*( PropertyVector3 const& rhs){ return Value * }
	//};

//#define ENGINE_PROPERTY(name, type)\
//	private: \
//		type name_;\
//	public:\
//		type Name();\
//		void Name(const type& value);\

}


