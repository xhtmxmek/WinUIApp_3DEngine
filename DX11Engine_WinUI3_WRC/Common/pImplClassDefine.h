#pragma once

#define SET_ACCESSOR( type, name )       inline void Set##name( const type& param )  { name = param; };
#define GET_ACCESSOR( type, name )       inline type Get##name() { return name; };
#define GET_SET_ACCESSOR( type, name )   SET_ACCESSOR( type, name ) GET_ACCESSOR( type, name )
#define GET_SET_ACCESSOR( type, name )   SET_ACCESSOR( type, name ) GET_ACCESSOR( type, name )

//#define SET_IMPL_ACCESSOR( type, name )		inline void Set##name( type param )  { pImpl->Set##name(param); };
//#define GET_IMPL_ACCESSOR( type, name )		inline type Get##name() { return pImpl->Get##name(); };
//#define GET_SET_IMPL_ACCESSOR( type, name ) SET_IMPL_ACCESSOR( type, name ) GET_IMPL_ACCESSOR( type, name )

#define IMPL_CLASS_PROPERTY(type, name) \
public:\	
	void GetTest();\

	

//#define IMPL_CLASS_PROPERTY_DEFEINITION(classType, type, name) \
//type classType::Get##name()\
//{\
//	return pImpl->Get##name();\
//}\
//void classType::Set##name(const type& param)\
//{\
//	pImpl->Set##name(param);\
//}