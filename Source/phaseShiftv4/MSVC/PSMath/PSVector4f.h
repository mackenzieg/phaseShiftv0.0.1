#pragma once
#pragma warning(disable : 4715)

#ifndef _PSVector4f_H_
#define _PSVector4f_H_

#include <ostream>
#include <assert.h>

#include "PSMath.h"

namespace PSMath
{
	class PSVector4f
	{
	public:
		float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;

	public:
		PSVector4f();
		PSVector4f(const PSVector4f&);
		PSVector4f(float, float, float, float);
		~PSVector4f();

		friend std::ostream& operator<<(std::ostream&, const PSVector4f&);

		friend bool operator==(const PSVector4f&, const PSVector4f&);
		friend bool operator!=(const PSVector4f&, const PSVector4f&);

		friend PSVector4f operator+(const PSVector4f&, const float&);
		friend PSVector4f operator+(const PSVector4f&, const PSVector4f&);
		friend PSVector4f operator-(const PSVector4f&, const float&);
		friend PSVector4f operator-(const PSVector4f&, const PSVector4f&);
		friend PSVector4f operator*(const PSVector4f&, float&);
		friend PSVector4f operator*(const PSVector4f&, const PSVector4f&);
		friend PSVector4f operator/(const PSVector4f&, float&);
		friend PSVector4f operator/(const PSVector4f&, const PSVector4f&);

		friend float DotProduct(const PSVector4f&, const PSVector4f&);
		friend PSVector4f Lerp(const PSVector4f&, const PSVector4f&, float);
		friend PSVector4f Clamp(const PSVector4f&, float, float);
		friend PSVector4f Min(const PSVector4f&, const PSVector4f&);
		friend PSVector4f Max(const PSVector4f&, const PSVector4f&);
		friend float DistanceBetween(const PSVector4f&, const PSVector4f&);
		friend float DistanceBetweenSquared(const PSVector4f&, const PSVector4f&);

		PSVector4f& operator=(const PSVector4f&);
		PSVector4f& operator+=(const float&);
		PSVector4f& operator+=(const PSVector4f&);
		PSVector4f& operator-=(const float&);
		PSVector4f& operator-=(const PSVector4f&);
		PSVector4f& operator*=(float);
		PSVector4f& operator*=(const PSVector4f&);
		PSVector4f& operator/=(float);
		PSVector4f& operator/=(const PSVector4f&);
		PSVector4f& operator-();
		float& operator[](int);

		void Set(float, float, float, float);
		void SetX(float);
		void SetY(float);
		void SetZ(float);
		void SetW(float);

		float Length() const;
		float LengthSquared() const;

		void MakeZero();
		bool IsZero() const;

		void Negate();

		void Normalize();
		bool IsNormalized() const;
	};

	inline PSVector4f::PSVector4f() : x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{
	}

	inline PSVector4f::PSVector4f(const PSVector4f& v) : x(v.x), y(v.y), z(v.z), w(v.w)
	{
	}

	inline PSVector4f::PSVector4f(float cx, float cy, float cz, float cw) : x(cx), y(cy), z(cz), w(cw)
	{
	}

	inline PSVector4f::~PSVector4f()
	{
	}

	inline std::ostream& operator<<(std::ostream& os, const PSVector4f& v)
	{
		os << '(' << v.x << ',' << v.y << ',' << v.z << ',' << v.w << ')';
		return os;
	}

	inline bool operator==(const PSVector4f& a, const PSVector4f& b)
	{
		return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w ? true : false;
	}

	inline bool operator!=(const PSVector4f& a, const PSVector4f& b)
	{
		return a == b ? false : true;
	}

	inline PSVector4f operator+(const PSVector4f& a, const float& b)
	{
		return PSVector4f(a.x + b, a.y + b, a.z + b, a.w + b);
	}

	inline PSVector4f operator+(const PSVector4f& a, const PSVector4f& b)
	{
		return PSVector4f(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}

	inline PSVector4f operator-(const PSVector4f& a, const float& b)
	{
		return PSVector4f(a.x - b, a.y - b, a.z - b, a.w - b);
	}

	inline PSVector4f operator-(const PSVector4f& a, const PSVector4f& b)
	{
		return PSVector4f(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

	inline PSVector4f operator*(const PSVector4f& a, float& b)
	{
		return PSVector4f(a.x * b, a.y * b, a.z * b, a.w * b);
	}

	inline PSVector4f operator*(const PSVector4f& a, const PSVector4f& b)
	{
		return PSVector4f(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
	}

	inline PSVector4f operator/(const PSVector4f& a, float& b)
	{
		assert(b != 0.0f);
		return PSVector4f(a.x / b, a.y / b, a.z / b, a.w / b);
	}

	inline PSVector4f operator/(const PSVector4f& a, const PSVector4f& b)
	{
		assert(b.x != 0.0f);
		assert(b.y != 0.0f);
		assert(b.z != 0.0f);
		assert(b.w != 0.0f);
		return PSVector4f(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
	}

	inline float DotProduct(const PSVector4f& a, const PSVector4f& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	inline PSVector4f Lerp(const PSVector4f& a, const PSVector4f& b, float c)
	{
		return PSVector4f(lerp(a.x, b.x, c), lerp(a.y, b.y, c), lerp(a.z, b.z, c), lerp(a.w, b.w, c));
	}

	inline PSVector4f Clamp(const PSVector4f& a, float b, float c)
	{
		return PSVector4f(clamp(a.x, b, c), clamp(a.y, b, c), clamp(a.z, b, c), clamp(a.w, b, c));
	}

	inline PSVector4f Min(const PSVector4f& a, const PSVector4f& b)
	{
		return PSVector4f(Min(a.x, b.x), Min(a.y, b.y), Min(a.z, b.z), Min(a.w, b.w));
	}

	inline PSVector4f Max(const PSVector4f& a, const PSVector4f& b)
	{
		return PSVector4f(Max(a.x, b.x), Max(a.y, b.y), Max(a.z, b.z), Max(a.w, b.w));
	}

	inline float DistanceBetween(const PSVector4f& a, const PSVector4f& b)
	{
		PSVector4f distance = a - b;
		return distance.Length();
	}

	inline float DistanceBetweenSquared(const PSVector4f& a, const PSVector4f& b)
	{
		PSVector4f distance = a - b;
		return distance.LengthSquared();
	}

	inline PSVector4f& PSVector4f::operator=(const PSVector4f& a)
	{
		x = a.x;
		y = a.y;
		z = a.z;
		w = a.w;
		return *this;
	}

	inline PSVector4f& PSVector4f::operator+=(const float& a)
	{
		x += a;
		y += a;
		z += a;
		w += a;
		return *this;
	}

	inline PSVector4f& PSVector4f::operator+=(const PSVector4f& a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
		w += a.w;
		return *this;
	}

	inline PSVector4f& PSVector4f::operator-=(const float& a)
	{
		x -= a;
		y -= a;
		z -= a;
		w -= a;
		return *this;
	}

	inline PSVector4f& PSVector4f::operator-=(const PSVector4f& a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
		w -= a.w;
		return *this;
	}

	inline PSVector4f& PSVector4f::operator*=(float a)
	{
		x *= a;
		y *= a;
		z *= a;
		w *= a;
		return *this;
	}

	inline PSVector4f& PSVector4f::operator*=(const PSVector4f& a)
	{
		x *= a.x;
		y *= a.y;
		z *= a.z;
		w *= a.w;
		return *this;
	}

	inline PSVector4f& PSVector4f::operator/=(float a)
	{
		assert(a != 0);
		a = 1.0f / a;
		x *= a;
		y *= a;
		z *= a;
		w *= a;
		return *this;
	}

	inline PSVector4f& PSVector4f::operator/=(const PSVector4f& a)
	{
		assert(a.x != 0.0f);
		assert(a.y != 0.0f);
		x /= a.x;
		y /= a.y;
		z /= a.z;
		w /= a.w;
		return *this;
	}

	inline PSVector4f& PSVector4f::operator-()
	{
		x = -x;
		y = -y;
		z = -z;
		w = -w;
		return *this;
	}

	// ReSharper disable CppNotAllPathsReturnValue
	inline float& PSVector4f::operator[](int i)
	{
		switch (i)
		{
		case(0) : return x;
		case(1) : return y;
		case(2) : return z;
		case(3) : return w;
		default: assert(!"[] Access error!");
		}
	}

	inline void PSVector4f::Set(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	inline void PSVector4f::SetX(float x)
	{
		this->x = x;
	}

	inline void PSVector4f::SetY(float y)
	{
		this->y = y;
	}

	inline void PSVector4f::SetZ(float z)
	{
		this->z = z;
	}

	inline void PSVector4f::SetW(float w)
	{
		this->w = w;
	}

	inline float PSVector4f::Length() const
	{
		return sqrtf(LengthSquared());
	}

	inline float PSVector4f::LengthSquared() const
	{
		return x * x + y * y + z * z + w * w;
	}

	inline void PSVector4f::MakeZero()
	{
		x = y = z = w = 0.0f;
	}

	inline bool PSVector4f::IsZero() const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f && w == 0.0f;
	}

	inline void PSVector4f::Negate()
	{
		x = -x;
		y = -y;
		z = -z;
		w = -w;
	}

	inline void PSVector4f::Normalize()
	{
		float magnitude = Length();
		assert(magnitude != 0.0f);

		magnitude = 1.0f / magnitude;

		x *= magnitude;
		y *= magnitude;
		z *= magnitude;
		w *= magnitude;
	}

	inline bool PSVector4f::IsNormalized() const
	{
		return Length() == 1.0f;
	}
}

#endif
