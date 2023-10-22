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
			TypeEnum,
			TypePath,
		};

		class PropertyBase
		{
		public:
			//OnChanged 함수 포인터를 넣어주면될듯
			//프로퍼티는 OnChanged 호출되면 Value를 넣어주어 Callback실행함
			//OnChange 이벤트에 여러개 실행시키고싶다면, OnChange를 벡터로 만들고 해당 이벤트에 바인딩시키기.
			PropertyBase(std::wstring const& name, PropertyType type, std::wstring const& category = L"Default")
				:name_(name), type_(type), category_(category)
			{
			}
			
			void ApplyChange() 
			{ 
				OnChange_(this); 
			}
			ENGINE_API std::wstring& Name()
			{
				return name_;
			}

			ENGINE_API std::wstring& Category()
			{
				return category_;
			}

			ENGINE_API PropertyType Type()
			{
				return type_;
			}

		private:
			std::wstring name_;
			std::wstring category_;
			PropertyType type_;
			std::function<void(PropertyBase*)> OnChange_;
			//std::vector<EngineProperty> child는 나중에 생각
		};

		class PropertyInt : public PropertyBase
		{
		public:
			PropertyInt(std::wstring const& name, std::wstring const& category)
				:PropertyBase(name, PropertyType::TypeInt, category),
				value_(0)
			{
			}
			PropertyInt& operator=(int value)
			{
				value_ = value; return (*this);
			}

			ENGINE_API int Value()
			{
				return value_;
			}
		private:
			int value_;
		};

		class PropertyFloat : public PropertyBase
		{
		public:
			PropertyFloat(std::wstring const& name, std::wstring const& category)
				:PropertyBase(name, PropertyType::TypeFloat, category),
				value_(0.0f)
			{
			}

			PropertyFloat& operator=(float value)
			{
				value_ = value; return (*this);
			}

			ENGINE_API  float Value()
			{
				return value_;
			}
		private:
			float value_;
		};

		class PropertyBool : public PropertyBase
		{
		public:
			PropertyBool(std::wstring const& name, std::wstring const& category)
				:PropertyBase(name, PropertyType::TypeBool, category),
				value_(false)
			{
			}
			PropertyBool& operator=(bool value)
			{
				value_ = value; return (*this);
			}

			ENGINE_API bool Value()
			{
				return value_;
			}
		private:
			bool value_;
		};

		//Property value는 Int. enum을 가지고 있고 UI에는 key값에 해당하는 String을 보여줌.
		class PropertyEnum : public PropertyBase
		{
		public:
			PropertyEnum(std::wstring const& name, std::wstring const& category)
				:PropertyBase(name, PropertyType::TypeEnum, category)
			{
			}

			void Register(const std::wstring& name, int value)
			{
				selectList_[value] = name;
			}

			PropertyEnum& operator=(int value)
			{
				value_ = value;
				return *this;
			}

		private:
			std::map<int, std::wstring> selectList_;
			int value_;
		};

		class PropertyPath : public PropertyBase
		{
		public:
			PropertyPath(std::wstring const& name, std::wstring const& category)
				:PropertyBase(name, PropertyType::TypePath, category)
			{
			}

			PropertyPath& operator=(const std::wstring& value)
			{
				value_ = value;
				return *this;
			}

			ENGINE_API const std::wstring& Value()
			{
				return value_;
			}

		private:			
			std::wstring value_;
		};

		class PropertyVector3 : public PropertyBase
		{
		public:
			PropertyVector3(std::wstring const& name, std::wstring const& category)
				: PropertyBase(name, PropertyType::TypeVector3, category),
				value_(0.0f, 0.0f, 0.0f) 
			{
			}
			const PropertyVector3& operator=(const Vector3f& value) { value_ = value; return *this; }

			ENGINE_API const Vector3f& Value() const
			{
				return value_;
			}

			ENGINE_API const Vector3f& operator()()
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


