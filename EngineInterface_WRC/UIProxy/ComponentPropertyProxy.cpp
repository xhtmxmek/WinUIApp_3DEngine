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
		* 1.엔진의 값이 float이면 float을 스트링으로 패킹.
		* vector3이면 string으로 패킹.
		* 저작도구에서 타입에 따라 스트링을 언패킹.
		* 2. 대응 되는 타입을 idl에 선언 (float3, float2, float). 그냥 case로 추가해주는게 나을듯.
		*/
	}
}
