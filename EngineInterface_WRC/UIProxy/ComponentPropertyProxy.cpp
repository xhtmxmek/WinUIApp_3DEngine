#include "pch.h"
#include "ComponentPropertyProxy.h"
#include "ComponentPropertyProxy.g.cpp"

namespace winrt::EngineInterface_WRC::implementation
{
	ComponentPropertyProxy::ComponentPropertyProxy(const hstring& name)
		:name_(name)
	{
	}
	hstring ComponentPropertyProxy::Name()
	{
		return name_;
	}
	hstring ComponentPropertyProxy::Value()
	{
		return value_;
	}
	void ComponentPropertyProxy::Value(hstring const& value)
	{
		value_ = value;
		/*
		* 1.������ ���� float�̸� float�� ��Ʈ������ ��ŷ.
		* vector3�̸� string���� ��ŷ.
		* ���۵������� Ÿ�Կ� ���� ��Ʈ���� ����ŷ.
		* 2. ���� �Ǵ� Ÿ���� idl�� ���� (float3, float2, float). �׳� case�� �߰����ִ°� ������.
		*/
	}
}
