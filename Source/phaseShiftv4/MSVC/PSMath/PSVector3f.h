#pragma once

#pragma warning(disable : 4715)

#ifndef _PSVector3f_H_
#define _PSVector3f_H_

#include <ostream>
#include <assert.h>

#include "PSMath.h"

namespace PSMath
{
	class PSVector3f
	{
	public:
		float x = 0.0f, y = 0.0f, z = 0.0f;

	public:
		PSVector3f();
		PSVector3f(const PSVector3f&);
		PSVector3f(float, float, float);
		~PSVector3f();

		friend std::ostream& operator<<(std::ostream&, const PSVector3f&);

		friend bool operator==(const PSVector3f&, const PSVector3f&);
		friend bool operator!=(const PSVector3f&, const PSVector3f&);

		friend PSVector3f operator+(const PSVector3f&, const float&);
		friend PSVector3f operator+(const PSVector3f&, const PSVector3f&);
		friend PSVector3f operator-(const PSVector3f&, const float&);
		friend PSVector3f operator-(const PSVector3f&, const PSVector3f&);
		friend PSVector3f operator*(const PSVector3f&, float&);
		friend PSVector3f operator*(const PSVector3f&, const PSVector3f&);
		friend PSVector3f operator/(const PSVector3f&, float&);
		friend PSVector3f operator/(const PSVector3f&, const PSVector3f&);

		friend float DotProduct(const PSVector3f&, const PSVector3f&);
		friend PSVector3f CrossProduct(const PSVector3f&, const PSVector3f&);
		friend float ScalarProjection(const PSVector3f&, const PSVector3f&);
		friend PSVector3f VectorProjection(const PSVector3f&, const PSVector3f&);
		friend PSVector3f Lerp(const PSVector3f&, const PSVector3f&, float);
		friend PSVector3f Clamp(const PSVector3f&, float, float);
		friend PSVector3f Min(const PSVector3f&, const PSVector3f&);
		friend PSVector3f Max(const PSVector3f&, const PSVector3f&);
		friend float DistanceBetween(const PSVector3f&, const PSVector3f&);
		friend float DistanceBetweenSquared(const PSVector3f&, const PSVector3f&);

		PSVector3f rotateX(const float&) const;
		PSVector3f rotateY(const float&) const;
		PSVector3f rotateZ(const float&) const;

		PSVector3f& operator=(const PSVector3f&);
		PSVector3f& operator+=(const float&);
		PSVector3f& operator+=(const PSVector3f&);
		PSVector3f& operator-=(const float&);
		PSVector3f& operator-=(const PSVector3f&);
		PSVector3f& operator*=(float);
		PSVector3f& operator*=(const PSVector3f&);
		PSVector3f& operator/=(float);
		PSVector3f& operator/=(const PSVector3f&);
		PSVector3f& operator-();
		float& operator[](int);

		void Set(float, float, float);
		void SetX(float);
		void SetY(float);
		void SetZ(float);

		float Length() const;
		float LengthSquared() const;

		void MakeZero();
		bool IsZero() const;

		void Negate();

		void Normalize();
		bool IsNormalized() const;
	};

	inline PSVector3f::PSVector3f() : x(0.0f), y(0.0f), z(0.0f)
	{
	}

	inline PSVector3f::PSVector3f(const PSVector3f& v) : x(v.x), y(v.y), z(v.z)
	{
	}

	inline PSVector3f::PSVector3f(float cx, float cy, float cz) : x(cx), y(cy), z(cz)
	{
	}

	inline PSVector3f::~PSVector3f()
	{
	}

	inline std::ostream& operator<<(std::ostream& os, const PSVector3f& v)
	{
		os << '(' << v.x << ',' << v.y << ',' << v.z << ')';
		return os;
	}

	inline bool operator==(const PSVector3f& a, const PSVector3f& b)
	{
		return a.x == b.x && a.y == b.y && a.z == b.z ? true : false;
	}

	inline bool operator!=(const PSVector3f& a, const PSVector3f& b)
	{
		return a == b ? false : true;
	}

	inline PSVector3f operator+(const PSVector3f& a, const float& b)
	{
		return PSVector3f(a.x + b, a.y + b, a.z + b);
	}

	inline PSVector3f operator+(const PSVector3f& a, const PSVector3f& b)
	{
		return PSVector3f(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	inline PSVector3f operator-(const PSVector3f& a, const float& b)
	{
		return PSVector3f(a.x - b, a.y - b, a.z - b);
	}

	inline PSVector3f operator-(const PSVector3f& a, const PSVector3f& b)
	{
		return PSVector3f(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	inline PSVector3f operator*(const PSVector3f& a, float& b)
	{
		return PSVector3f(a.x * b, a.y * b, a.z * b);
	}

	inline PSVector3f operator*(const PSVector3f& a, const PSVector3f& b)
	{
		return PSVector3f(a.x * b.x, a.y * b.y, a.z * b.z);
	}

	inline PSVector3f operator/(const PSVector3f& a, float& b)
	{
		assert(b != 0.0f);
		return PSVector3f(a.x / b, a.y / b, a.z / b);
	}

	inline PSVector3f operator/(const PSVector3f& a, const PSVector3f& b)
	{
		assert(b.x != 0.0f);
		assert(b.y != 0.0f);
		return PSVector3f(a.x / b.x, a.y / b.y, a.z / b.z);
	}

	inline float DotProduct(const PSVector3f& a, const PSVector3f& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	inline PSVector3f CrossProduct(const PSVector3f& a, const PSVector3f& b)
	{
		return PSVector3f((a.y * b.z) - (a.z * b.y), (a.z * b.x) - (a.x * b.z), (a.x * b.y) - (a.y * b.x));
	}

	//Maybe Incorrect
	inline float ScalarProjection(const PSVector3f& a, const PSVector3f& b)
	{
		return DotProduct(a, b) / b.Length();
	}

	//Maybe Incorrect
	inline PSVector3f VectorProjection(const PSVector3f& a, const PSVector3f& b)
	{
		float dotAB = DotProduct(a, b);
		float rx = dotAB * b.x / b.LengthSquared();
		float ry = dotAB * b.y / b.LengthSquared();
		float rz = dotAB * b.z / b.LengthSquared();
		return PSVector3f(rx, ry, rz);
	}

	inline PSVector3f Lerp(const PSVector3f& a, const PSVector3f& b, float c)
	{
		return PSVector3f(lerp(a.x, b.x, c), lerp(a.y, b.y, c), lerp(a.z, b.z, c));
	}

	inline PSVector3f Clamp(const PSVector3f& a, float b, float c)
	{
		return PSVector3f(clamp(a.x, b, c), clamp(a.y, b, c), clamp(a.z, b, c));
	}

	inline PSVector3f Min(const PSVector3f& a, const PSVector3f& b)
	{
		return PSVector3f(Min(a.x, b.x), Min(a.y, b.y), Min(a.z, b.z));
	}

	inline PSVector3f Max(const PSVector3f& a, const PSVector3f& b)
	{
		return PSVector3f(Max(a.x, b.x), Max(a.y, b.y), Max(a.z, b.z));
	}

	inline float DistanceBetween(const PSVector3f& a, const PSVector3f& b)
	{
		PSVector3f distance = a - b;
		return distance.Length();
	}

	inline float DistanceBetweenSquared(const PSVector3f& a, const PSVector3f& b)
	{
		PSVector3f distance = a - b;
		return distance.LengthSquared();
	}

	inline PSVector3f PSVector3f::rotateX(const float& radians) const
	{
		float x_ = x;
		float y_ = y * cos(radians) - z * sin(radians);
		float z_ = y * sin(radians) + z * cos(radians);
		return PSVector3f(x_, y_, z_);
	}

	inline PSVector3f PSVector3f::rotateY(const float& radians) const
	{
		float x_ = x * cos(radians) + z * sin(radians);
		float y_ = y;
		float z_ = -x * sin(radians) + z * cos(radians);
		return PSVector3f(x_, y_, z_);
	}

	inline PSVector3f PSVector3f::rotateZ(const float& radians) const
	{
		float x_ = x * cos(radians) - y * sin(radians);
		float y_ = x * sin(radians) + y * cos(radians);
		float z_ = z;
		return PSVector3f(x_, y_, z_);
	}

	inline PSVector3f& PSVector3f::operator=(const PSVector3f& a)
	{
		x = a.x;
		y = a.y;
		z = a.z;
		return *this;
	}

	inline PSVector3f& PSVector3f::operator+=(const float& a)
	{
		x += a;
		y += a;
		z += a;
		return *this;
	}

	inline PSVector3f& PSVector3f::operator+=(const PSVector3f& a)
	{
		x += a.x;
		y += a.y;
		z += a.z;
		return *this;
	}

	inline PSVector3f& PSVector3f::operator-=(const float& a)
	{
		x -= a;
		y -= a;
		z -= a;
		return *this;
	}

	inline PSVector3f& PSVector3f::operator-=(const PSVector3f& a)
	{
		x -= a.x;
		y -= a.y;
		z -= a.z;
		return *this;
	}

	inline PSVector3f& PSVector3f::operator*=(float a)
	{
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}

	inline PSVector3f& PSVector3f::operator*=(const PSVector3f& a)
	{
		x *= a.x;
		y *= a.y;
		z *= a.z;
		return *this;
	}

	inline PSVector3f& PSVector3f::operator/=(float a)
	{
		assert(a != 0);
		a = 1.0f / a;
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}

	inline PSVector3f& PSVector3f::operator/=(const PSVector3f& a)
	{
		assert(a.x != 0.0f);
		assert(a.y != 0.0f);
		x /= a.x;
		y /= a.y;
		z /= a.z;
		return *this;
	}

	inline PSVector3f& PSVector3f::operator-()
	{
		x = -x;
		y = -y;
		z = -z;
		return *this;
	}

	// ReSharper disable CppNotAllPathsReturnValue
	inline float& PSVector3f::operator[](int i)
	{
		switch (i)
		{
		case(0) : return x;
		case(1) : return y;
		case(2) : return z;
		default: assert(!"[] Access error!");
		}
	}

	inline void PSVector3f::Set(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	inline void PSVector3f::SetX(float x)
	{
		this->x = x;
	}

	inline void PSVector3f::SetY(float y)
	{
		this->y = y;
	}

	inline void PSVector3f::SetZ(float z)
	{
		this->z = z;
	}

	inline float PSVector3f::Length() const
	{
		return sqrtf(LengthSquared());
	}

	inline float PSVector3f::LengthSquared() const
	{
		return x * x + y * y + z * z;
	}

	inline void PSVector3f::MakeZero()
	{
		x = y = z = 0.0f;
	}

	inline bool PSVector3f::IsZero() const
	{
		return x == 0.0f && y == 0.0f && z == 0.0f;
	}

	inline void PSVector3f::Negate()
	{
		x = -x;
		y = -y;
		z = -z;
	}

	inline void PSVector3f::Normalize()
	{
		float magnitude = Length();
		assert(magnitude != 0.0f);

		magnitude = 1.0f / magnitude;

		x *= magnitude;
		y *= magnitude;
		z *= magnitude;
	}

	inline bool PSVector3f::IsNormalized() const
	{
		return Length() == 1.0f;
	}
}

#endif
