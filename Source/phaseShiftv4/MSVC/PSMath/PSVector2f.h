#pragma once
#pragma warning(disable : 4715)

#ifndef _PSVector2f_H_
#define _PSVector2f_H_

#include <ostream>
#include <assert.h>

#include "PSMath.h"

namespace PSMath
{
	class PSVector2f
	{
	public:
		float x = 0.0f, y = 0.0f;

	public:
		PSVector2f();
		PSVector2f(const PSVector2f&);
		PSVector2f(float, float);
		~PSVector2f();

		friend std::ostream& operator<<(std::ostream&, const PSVector2f&);

		friend bool operator==(const PSVector2f&, const PSVector2f&);
		friend bool operator!=(const PSVector2f&, const PSVector2f&);

		friend PSVector2f operator+(const PSVector2f&, const PSVector2f&);
		friend PSVector2f operator+(const PSVector2f&, const float&);
		friend PSVector2f operator-(const PSVector2f&, const PSVector2f&);
		friend PSVector2f operator-(const PSVector2f&, const float&);
		friend PSVector2f operator*(const PSVector2f& v, float);
		friend PSVector2f operator*(const PSVector2f&, const PSVector2f&);
		friend PSVector2f operator/(const PSVector2f&, float);
		friend PSVector2f operator/(const PSVector2f&, const PSVector2f&);

		friend float DotProduct(const PSVector2f&, const PSVector2f&);
		friend float ScalarProjection(const PSVector2f&, const PSVector2f&);
		friend PSVector2f VectorProjection(const PSVector2f&, const PSVector2f&);
		friend PSVector2f Lerp(const PSVector2f&, const PSVector2f&, float);
		friend PSVector2f Clamp(const PSVector2f&, float, float);
		friend PSVector2f Min(const PSVector2f&, const PSVector2f&);
		friend PSVector2f Max(const PSVector2f&, const PSVector2f&);
		friend float DistanceBetween(const PSVector2f&, const PSVector2f&);
		friend float DistanceBetweenSquared(const PSVector2f&, const PSVector2f&);

		PSVector2f Rotate(const float&) const;

		PSVector2f& operator=(const PSVector2f&);
		PSVector2f& operator+=(const float&);
		PSVector2f& operator+=(const PSVector2f&);
		PSVector2f& operator-=(const float&);
		PSVector2f& operator-=(const PSVector2f&);
		PSVector2f& operator*=(float);
		PSVector2f& operator*=(const PSVector2f&);
		PSVector2f& operator/=(float);
		PSVector2f& operator/=(const PSVector2f&);
		PSVector2f& operator-();
		float& operator[](int);

		void Set(float, float);
		void SetX(float);
		void SetY(float);

		float Length() const;
		float LengthSquared() const;

		void MakeZero();
		bool IsZero() const;

		void Negate();

		void Normalize();
		bool IsNormalized() const;
	};

	inline PSVector2f::PSVector2f() : x(0.0f), y(0.0f)
	{
	}

	inline PSVector2f::PSVector2f(const PSVector2f& v) : x(v.x), y(v.y)
	{
	}

	inline PSVector2f::PSVector2f(float cx, float cy) : x(cx), y(cy)
	{
	}

	inline PSVector2f::~PSVector2f()
	{
	}

	inline std::ostream& operator<<(std::ostream& os, const PSVector2f& v)
	{
		os << '(' << v.x << ',' << v.y << ')';
		return os;
	}

	inline bool operator==(const PSVector2f& a, const PSVector2f& b)
	{
		return a.x == b.x && a.y == b.y ? true : false;
	}

	inline bool operator!=(const PSVector2f& a, const PSVector2f& b)
	{
		return a == b ? false : true;
	}

	inline PSVector2f operator+(const PSVector2f& a, const PSVector2f& b)
	{
		return PSVector2f(a.x + b.x, a.y + b.y);
	}

	inline PSVector2f operator+(const PSVector2f& a, const float& b)
	{
		return PSVector2f(a.x + b, a.y + b);
	}

	inline PSVector2f operator-(const PSVector2f& a, const PSVector2f& b)
	{
		return PSVector2f(a.x - b.x, a.y - b.y);
	}

	inline PSVector2f operator-(const PSVector2f& a, const float& b)
	{
		return PSVector2f(a.x - b, a.y - b);
	}

	inline PSVector2f operator*(const PSVector2f& a, float b)
	{
		return PSVector2f(a.x * b, a.y * b);
	}

	inline PSVector2f operator*(const PSVector2f& a, const PSVector2f& b)
	{
		return PSVector2f(a.x * b.x, a.y * b.y);
	}

	inline PSVector2f operator/(const PSVector2f& a, float b)
	{
		assert(b != 0.0f);
		return PSVector2f(a.x / b, a.y / b);
	}

	inline PSVector2f operator/(const PSVector2f& a, const PSVector2f& b)
	{
		assert(b.x != 0.0f);
		assert(b.y != 0.0f);
		return PSVector2f(a.x / b.x, a.y / b.y);
	}

	inline float DotProduct(const PSVector2f& a, const PSVector2f& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	inline float ScalarProjection(const PSVector2f& a, const PSVector2f& b)
	{
		return DotProduct(a, b) / b.Length();
	}

	inline PSVector2f VectorProjection(const PSVector2f& a, const PSVector2f& b)
	{
		float dotAB = DotProduct(a, b);
		float rx = dotAB * b.x / b.LengthSquared();
		float ry = dotAB * b.y / b.LengthSquared();
		return PSVector2f(rx, ry);
	}

	inline PSVector2f Lerp(const PSVector2f& a, const PSVector2f& b, float c)
	{
		return PSVector2f(lerp(a.x, b.x, c), lerp(a.y, b.y, c));
	}

	inline PSVector2f Clamp(const PSVector2f& a, float b, float c)
	{
		return PSVector2f(clamp(a.x, b, c), clamp(a.y, b, c));
	}

	inline PSVector2f Min(const PSVector2f& a, const PSVector2f& b)
	{
		return PSVector2f(Min(a.x, b.x), Min(a.y, b.y));
	}

	inline PSVector2f Max(const PSVector2f& a, const PSVector2f& b)
	{
		return PSVector2f(Max(a.x, b.x), Max(a.y, b.y));
	}

	inline float DistanceBetween(const PSVector2f& a, const PSVector2f& b)
	{
		PSVector2f distance = a - b;
		return distance.Length();
	}

	inline float DistanceBetweenSquared(const PSVector2f& a, const PSVector2f& b)
	{
		PSVector2f distance = a - b;
		return distance.LengthSquared();
	}

	inline PSVector2f PSVector2f::Rotate(const float& radians) const
	{
		float ca = cos(radians);
		float sa = sin(radians);
		return PSVector2f(ca * x - sa * y, sa * x + ca * y);
	}

	inline PSVector2f& PSVector2f::operator=(const PSVector2f& a)
	{
		x = a.x;
		y = a.y;
		return *this;
	}

	inline PSVector2f& PSVector2f::operator+=(const float& a)
	{
		x += a;
		y += a;
		return *this;
	}

	inline PSVector2f& PSVector2f::operator+=(const PSVector2f& a)
	{
		x += a.x;
		y += a.y;
		return *this;
	}

	inline PSVector2f& PSVector2f::operator-=(const float& a)
	{
		x -= a;
		y -= a;
		return *this;
	}

	inline PSVector2f& PSVector2f::operator-=(const PSVector2f& a)
	{
		x -= a.x;
		y -= a.y;
		return *this;
	}

	inline PSVector2f& PSVector2f::operator*=(float a)
	{
		x *= a;
		y *= a;
		return *this;
	}

	inline PSVector2f& PSVector2f::operator*=(const PSVector2f& a)
	{
		x *= a.x;
		y *= a.y;
		return *this;
	}

	inline PSVector2f& PSVector2f::operator/=(float a)
	{
		assert(a != 0);
		a = 1.0f / a;
		x *= a;
		y *= a;
		return *this;
	}

	inline PSVector2f& PSVector2f::operator/=(const PSVector2f& a)
	{
		assert(a.x != 0.0f);
		assert(a.y != 0.0f);
		x /= a.x;
		y /= a.y;
		return *this;
	}

	inline PSVector2f& PSVector2f::operator-()
	{
		x = -x;
		y = -y;
		return *this;
	}

	// ReSharper disable CppNotAllPathsReturnValue
	inline float& PSVector2f::operator[](int i)
	{
		switch (i)
		{
		case(0) : return x;
		case(1) : return y;
		default: assert(!"[] Access error!");
		}
	}

	inline void PSVector2f::Set(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	inline void PSVector2f::SetX(float x)
	{
		this->x = x;
	}

	inline void PSVector2f::SetY(float y)
	{
		this->y = y;
	}

	inline float PSVector2f::Length() const
	{
		return sqrtf(LengthSquared());
	}

	inline float PSVector2f::LengthSquared() const
	{
		return x * x + y * y;
	}

	inline void PSVector2f::MakeZero()
	{
		x = y = 0.0f;
	}

	inline bool PSVector2f::IsZero() const
	{
		return x == 0.0f && y == 0.0f;
	}

	inline void PSVector2f::Negate()
	{
		x = -x;
		y = -y;
	}

	inline void PSVector2f::Normalize()
	{
		float magnitude = Length();
		assert(magnitude != 0.0f);

		magnitude = 1.0f / magnitude;

		x *= magnitude;
		y *= magnitude;
	}

	inline bool PSVector2f::IsNormalized() const
	{
		return Length() == 1.0f;
	}
}

#endif
