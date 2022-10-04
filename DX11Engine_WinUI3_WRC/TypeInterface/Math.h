#pragma once
#include "DLLDefine.h"

namespace Engine
{
	namespace Type
	{
		class FVector2
		{
		public:
			FVector2() = default;
			~FVector2() = default;
			float x;
			float y;
			FVector2 Test() { return FVector2(); }
		};
		//class FVector2Impl
		//{
		//public:
		//	FVector2Impl() = default;

		//	 DirectX::SimpleMath::Vector2 Data;

		//};

		//class ENGINE_API FVector2
		//{
		//public:
		//	FVector2()
		//	{
		//		pImpl = new FVector2Impl();
		//	}

		//	~FVector2()
		//	{
		//		delete pImpl;
		//	}

		//	FVector2(const FVector2& src)
		//		:FVector2()
		//	{
		//		pImpl->Data = src.pImpl->Data;
		//	}

		//	FVector2(const DirectX::SimpleMath::Vector2& src)
		//		:FVector2()
		//	{
		//		pImpl->Data = src;
		//	}

		//	// Assignment operators
		//	void operator=(const FVector2& src) { pImpl->Data = src.pImpl->Data; }
		//	void operator=(const DirectX::SimpleMath::Vector2& src) { pImpl->Data = src; }
		//	Vector2& operator+= (const Vector2& V) noexcept 
		//	{ 
		//		pImpl->Data += V;
		//	};
		//	Vector2& operator-= (const Vector2& V) noexcept;
		//	Vector2& operator*= (const Vector2& V) noexcept;
		//	Vector2& operator*= (float S) noexcept;
		//	Vector2& operator/= (float S) noexcept;

		//	// Comparison operators
		//	bool operator == (const Vector2& V) const noexcept;
		//	bool operator != (const Vector2& V) const noexcept;
		//	
		//	// Unary operators
		//	Vector2 operator+ () const noexcept { return *this; }
		//	Vector2 operator- () const noexcept { return Vector2(-x, -y); }

		//	// Vector operations
		//	bool InBounds(const Vector2& Bounds) const noexcept;

		//	float Length() const noexcept;
		//	float LengthSquared() const noexcept;

		//	float Dot(const Vector2& V) const noexcept;
		//	void Cross(const Vector2& V, Vector2& result) const noexcept;
		//	Vector2 Cross(const Vector2& V) const noexcept;

		//	void Normalize() noexcept;
		//	void Normalize(Vector2& result) const noexcept;

		//	void Clamp(const Vector2& vmin, const Vector2& vmax) noexcept;
		//	void Clamp(const Vector2& vmin, const Vector2& vmax, Vector2& result) const noexcept;

		//	// Static functions
		//	static float Distance(const Vector2& v1, const Vector2& v2) noexcept;
		//	static float DistanceSquared(const Vector2& v1, const Vector2& v2) noexcept;

		//	static void Min(const Vector2& v1, const Vector2& v2, Vector2& result) noexcept;
		//	static Vector2 Min(const Vector2& v1, const Vector2& v2) noexcept;

		//	static void Max(const Vector2& v1, const Vector2& v2, Vector2& result) noexcept;
		//	static Vector2 Max(const Vector2& v1, const Vector2& v2) noexcept;

		//	static void Lerp(const Vector2& v1, const Vector2& v2, float t, Vector2& result) noexcept;
		//	static Vector2 Lerp(const Vector2& v1, const Vector2& v2, float t) noexcept;

		//	static void SmoothStep(const Vector2& v1, const Vector2& v2, float t, Vector2& result) noexcept;
		//	static Vector2 SmoothStep(const Vector2& v1, const Vector2& v2, float t) noexcept;

		//	static void Barycentric(const Vector2& v1, const Vector2& v2, const Vector2& v3, float f, float g, Vector2& result) noexcept;
		//	static Vector2 Barycentric(const Vector2& v1, const Vector2& v2, const Vector2& v3, float f, float g) noexcept;

		//	static void CatmullRom(const Vector2& v1, const Vector2& v2, const Vector2& v3, const Vector2& v4, float t, Vector2& result) noexcept;
		//	static Vector2 CatmullRom(const Vector2& v1, const Vector2& v2, const Vector2& v3, const Vector2& v4, float t) noexcept;

		//	static void Hermite(const Vector2& v1, const Vector2& t1, const Vector2& v2, const Vector2& t2, float t, Vector2& result) noexcept;
		//	static Vector2 Hermite(const Vector2& v1, const Vector2& t1, const Vector2& v2, const Vector2& t2, float t) noexcept;

		//	static void Reflect(const Vector2& ivec, const Vector2& nvec, Vector2& result) noexcept;
		//	static Vector2 Reflect(const Vector2& ivec, const Vector2& nvec) noexcept;

		//	static void Refract(const Vector2& ivec, const Vector2& nvec, float refractionIndex, Vector2& result) noexcept;
		//	static Vector2 Refract(const Vector2& ivec, const Vector2& nvec, float refractionIndex) noexcept;

		//	static void Transform(const Vector2& v, const Quaternion& quat, Vector2& result) noexcept;
		//	static Vector2 Transform(const Vector2& v, const Quaternion& quat) noexcept;

		//	static void Transform(const Vector2& v, const Matrix& m, Vector2& result) noexcept;
		//	static Vector2 Transform(const Vector2& v, const Matrix& m) noexcept;
		//	static void Transform(_In_reads_(count) const Vector2* varray, size_t count, const Matrix& m, _Out_writes_(count) Vector2* resultArray) noexcept;

		//	static void Transform(const Vector2& v, const Matrix& m, Vector4& result) noexcept;
		//	static void Transform(_In_reads_(count) const Vector2* varray, size_t count, const Matrix& m, _Out_writes_(count) Vector4* resultArray) noexcept;

		//	static void TransformNormal(const Vector2& v, const Matrix& m, Vector2& result) noexcept;
		//	static Vector2 TransformNormal(const Vector2& v, const Matrix& m) noexcept;
		//	static void TransformNormal(_In_reads_(count) const Vector2* varray, size_t count, const Matrix& m, _Out_writes_(count) Vector2* resultArray) noexcept;

		//	//// Constants
		//	//static const Vector2 Zero;
		//	//static const Vector2 One;
		//	//static const Vector2 UnitX;
		//	//static const Vector2 UnitY;

		//	// Binary operators
		//	Vector2 operator+ (const Vector2& V1, const Vector2& V2) noexcept;
		//	Vector2 operator- (const Vector2& V1, const Vector2& V2) noexcept;
		//	Vector2 operator* (const Vector2& V1, const Vector2& V2) noexcept;
		//	Vector2 operator* (const Vector2& V, float S) noexcept;
		//	Vector2 operator/ (const Vector2& V1, const Vector2& V2) noexcept;
		//	Vector2 operator/ (const Vector2& V, float S) noexcept;
		//	Vector2 operator* (float S, const Vector2& V) noexcept;


		//private:
		//	FVector2Impl* pImpl;
		//};


		//class WStringImpl
		//{
		//public:
		//	WStringImpl() = default;

		//	std::wstring Data;

		//};

		//class ENGINE_API WString
		//{
		//public:
		//	WString()
		//	{
		//		pImpl = new WStringImpl();
		//	}

		//	~WString()
		//	{
		//		delete pImpl;
		//	}

		//	WString(const WString& src)
		//		:WString()
		//	{
		//		pImpl->Data = src.pImpl->Data;
		//	}

		//	WString(const std::wstring& src)
		//		:WString()
		//	{
		//		pImpl->Data = src;
		//	}

		//	void operator=(const WString& src) { pImpl->Data = src.pImpl->Data; }
		//	void operator=(const std::wstring& src) { pImpl->Data = src; }

		//private:
		//	WStringImpl* pImpl;
		//};
	}
}
