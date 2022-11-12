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
		//OnChanged 함수 포인터를 넣어주면될듯
		//프로퍼티는 OnChanged 호출되면 Value를 넣어주어 Callback실행함
		//OnChange 이벤트에 여러개 실행시키고싶다면, OnChange를 벡터로 만들고 해당 이벤트에 바인딩시키기.
		TypeBase(std::string const& name, PropertyType const& type)
			:name_(name), type_(type)
		{
		}
		std::function<void(TypeBase*)> OnChange;
		void ApplyChange() { OnChange(this); }
	private:
		std::string name_;
		PropertyType type_;
		//std::vector<EngineProperty> child는 나중에 생각
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
		//std::vector<EngineProperty> child는 나중에 생각
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
		//std::vector<EngineProperty> child는 나중에 생각
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

	//Property value는 Int. enum을 가지고 있고 UI에는 key값에 해당하는 String을 보여줌.
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
	//	//operator와 복사생성자 필요									
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


