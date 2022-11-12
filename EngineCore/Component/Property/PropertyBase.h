#pragma once
#include "pch.h"

namespace Engine
{
	namespace Component
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

		class PropertyBase
		{
		public:
			//OnChanged 함수 포인터를 넣어주면될듯
			//프로퍼티는 OnChanged 호출되면 Value를 넣어주어 Callback실행함
			//OnChange 이벤트에 여러개 실행시키고싶다면, OnChange를 벡터로 만들고 해당 이벤트에 바인딩시키기.
			PropertyBase(std::string const& name, PropertyType const& type)
				:name_(name), type_(type)
			{
			}
			std::function<void(PropertyBase*)> OnChange;
			void ApplyChange() { OnChange(this); }
		private:
			std::string name_;
			PropertyType type_;
			//std::vector<EngineProperty> child는 나중에 생각
		};

		class PropertyInt : public PropertyBase
		{
		public:
			PropertyInt(std::string const& name, PropertyType const& type)
				:PropertyBase(name, type),
				value_(0)
			{
			}
			PropertyInt& operator=(int value)
			{
				value_ = value; return (*this);
			}
		private:
			int value_;
			//std::vector<EngineProperty> child는 나중에 생각
		};

		class PropertyFloat : public PropertyBase
		{
		public:
			PropertyFloat(std::string const& name, PropertyType const& type)
				:PropertyBase(name, type),
				value_(0.0f)
			{
			}

			PropertyFloat& operator=(float value)
			{
				value_ = value; return (*this);
			}
		private:
			float value_;
			//std::vector<EngineProperty> child는 나중에 생각
		};

		class PropertBool : public PropertyBase
		{
		public:
			PropertBool(std::string const& name, PropertyType const& type)
				:PropertyBase(name, type),
				value_(false)
			{
			}
			PropertBool& operator=(bool value)
			{
				value_ = value; return (*this);
			}

		private:
			bool value_;
		};

		//Property value는 Int. enum을 가지고 있고 UI에는 key값에 해당하는 String을 보여줌.
		class PropertyEnum : public PropertyInt
		{
		public:
			PropertyEnum(std::string const& name, PropertyType const& type)
				:PropertyInt(name, type)
			{
			}

			void Register(const std::string& name, int value)
			{
				selectList_[value] = name;
			}

			PropertyEnum& operator=(int value)
			{
				(PropertyInt::operator=(value));
				return *this;
			}
		private:
			std::map<int, string> selectList_;
		};

		class PropertyVector3 : public PropertyBase
		{
		public:
			PropertyVector3(std::string const& name, PropertyType const& type)
				: PropertyBase(name, type), value_(0.0f, 0.0f, 0.0f) 
			{
			}
			const PropertyVector3& operator=(const Vector3f& value) { value_ = value; return *this; }

			const Vector3f& Value()
			{
				return value_;
			}
		private:
			Vector3f value_;
		};

	//#define ENGINE_PROPERTY(name, type)\
	//	private: \
	//		type name_;\
	//	public:\
	//		type Name();\
	//		void Name(const type& value);\
	
	}
}


