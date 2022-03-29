#pragma once

namespace Engine
{
	namespace Component
	{
		class EngineProperty
		{
		public:
			//OnChanged �Լ� �����͸� �־��ָ�ɵ�
			//������Ƽ�� OnChanged ȣ��Ǹ� Value�� �־��־� Callback������
			//OnChange �̺�Ʈ�� ������ �����Ű��ʹٸ�, OnChange�� ���ͷ� ����� �ش� �̺�Ʈ�� ���ε���Ű��.
			EngineProperty(std::string const& name, PropertyType const& type)
				:Name(name), Type(type) {}
			std::function<void(EngineProperty*)> OnChange;
			void ApplyChange() { OnChange(this); }
		private:
			std::string Name;
			PropertyType Type;
			//std::vector<EngineProperty> child�� ���߿� ����
		};

		class PropertyBool : public EngineProperty
		{
			//operator�� ��������� �ʿ�									
		public:
			PropertyBool(std::string const& name, PropertyType const& type, const bool& src)
				:EngineProperty(name, type), Value(src) {}
			const PropertyBool& operator=(const bool& value) { Value = value; return *this; }
			const bool GetValue() const { return Value; }
		private:
			bool Value;
		};

		class PropertyVector3 : public EngineProperty
		{
		public:
			PropertyVector3(std::string const& name, PropertyType const& type, const Vector3& src)
				: EngineProperty(name, type), Value(src) {}
			const PropertyVector3& operator=(const Vector3& value) { Value = value; return *this; }
			const Vector3& GetValue() const { return Value; }
			const Vector3& operator()() { return Value; }
			//const Vector3& operator*( PropertyVector3 const& rhs){ return Value * }
		private:
			Vector3 Value;
		};
	}
}


