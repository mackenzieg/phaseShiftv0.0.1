#pragma once

#ifndef _PSVector2f_s_H_
#define _PSVector2f_s_H_

#include <ostream>
#include <assert.h>

#include "PSMath.h"
#include "PSMath_s.h"
#include "PSFloat.h"

namespace PSMath
{
	class PSVector2f_s
	{
	public:
		__m128 vec;

	public:
		PSVector2f_s();
		PSVector2f_s(const PSVector2f_s&);
		PSVector2f_s(float, float);
		explicit PSVector2f_s(__m128);
		~PSVector2f_s();

		friend std::ostream& operator<<(std::ostream&, const PSVector2f_s&);

		friend bool operator==(const PSVector2f_s&, const PSVector2f_s&);
		friend bool operator!=(const PSVector2f_s&, const PSVector2f_s&);

		friend PSVector2f_s operator+(const PSVector2f_s&, const PSVector2f_s&);
		friend PSVector2f_s operator+(const PSVector2f_s&, const float&);
		friend PSVector2f_s operator+(const PSVector2f_s&, const __m128&);
		friend PSVector2f_s operator-(const PSVector2f_s&, const PSVector2f_s&);
		friend PSVector2f_s operator-(const PSVector2f_s&, const float&);
		friend PSVector2f_s operator-(const PSVector2f_s&, const __m128&);
		friend PSVector2f_s operator*(const PSVector2f_s&, const float&);
		friend PSVector2f_s operator*(const PSVector2f_s&, const PSVector2f_s&);
		friend PSVector2f_s operator*(const PSVector2f_s&, const __m128&);
		friend PSVector2f_s operator/(const PSVector2f_s&, const float&);
		friend PSVector2f_s operator/(const PSVector2f_s&, const PSVector2f_s&);
		friend PSVector2f_s operator/(const PSVector2f_s&, const __m128&);

		friend int DotProduct(const PSVector2f_s&, const PSVector2f_s&);
		friend PSVector2f_s Lerp(const PSVector2f_s&, const PSVector2f_s&, float);
		friend PSVector2f_s Clamp(const PSVector2f_s&, float, float);
		friend PSVector2f_s Min(const PSVector2f_s&, const PSVector2f_s&);
		friend PSVector2f_s Max(const PSVector2f_s&, const PSVector2f_s&);
		friend float DistanceBetween(const PSVector2f_s&, const PSVector2f_s&);
		friend float DistanceBetweenSquared(const PSVector2f_s&, const PSVector2f_s&);
	};

	inline PSVector2f_s::PSVector2f_s() : vec(_mm_set1_ps(0))
	{
	}

	inline PSVector2f_s::PSVector2f_s(const PSVector2f_s& a) : vec(a.vec)
	{
	}

	inline PSVector2f_s::PSVector2f_s(float a, float b) : PSVector2f_s()
	{
		float ALIGN_16 f[4] = { a, b, 0, 0 };
		vec = _mm_load_ps(f);
	}

	inline PSVector2f_s::PSVector2f_s(__m128 a) : vec(a)
	{
	}

	inline PSVector2f_s::~PSVector2f_s()
	{
	}

	inline std::ostream& operator<<(std::ostream& os, const PSVector2f_s& v)
	{
		os << '(' << vectorGetByIndex<0>(v.vec) << ',' << vectorGetByIndex<1>(v.vec) << ')';
		return os;
	}

	inline bool operator==(const PSVector2f_s& a, const PSVector2f_s& b)
	{
		__m128 result = _mm_cmpeq_ps(a.vec, b.vec);
		return isnan(result.m128_f32[0]) && isnan(result.m128_f32[1]) && isnan(result.m128_f32[2]) && isnan(result.m128_f32[3]);
	}

	inline bool operator!=(const PSVector2f_s& a, const PSVector2f_s& b)
	{
		return a == b ? false : true;
	}

	inline PSVector2f_s operator+(const PSVector2f_s& a, const PSVector2f_s& b)
	{
		return PSVector2f_s(_mm_add_ps(a.vec, b.vec));
	}

	inline PSVector2f_s operator+(const PSVector2f_s& a, const float& b)
	{
		__m128 scalar = _mm_set1_ps(b);
		return PSVector2f_s(_mm_add_ps(a.vec, scalar));
	}

	inline PSVector2f_s operator+(const PSVector2f_s& a, const __m128& b)
	{
		return PSVector2f_s(_mm_add_ps(a.vec, b));
	}

	inline PSVector2f_s operator-(const PSVector2f_s& a, const PSVector2f_s& b)
	{
		return PSVector2f_s(_mm_sub_ps(a.vec, b.vec));
	}

	inline PSVector2f_s operator-(const PSVector2f_s& a, const float& b)
	{
		__m128 scalar = _mm_set1_ps(b);
		return PSVector2f_s(_mm_sub_ps(a.vec, scalar));
	}

	inline PSVector2f_s operator-(const PSVector2f_s& a, const __m128& b)
	{
		return PSVector2f_s(_mm_sub_ps(a.vec, b));
	}

	inline PSVector2f_s operator*(const PSVector2f_s& a, const PSVector2f_s& b)
	{
		return PSVector2f_s(_mm_mul_ps(a.vec, b.vec));
	}

	inline PSVector2f_s operator*(const PSVector2f_s& a, const float& b)
	{
		__m128 scalar = _mm_set1_ps(b);
		return PSVector2f_s(_mm_mul_ps(a.vec, scalar));
	}

	inline PSVector2f_s operator*(const PSVector2f_s& a, const __m128& b)
	{
		return PSVector2f_s(_mm_mul_ps(a.vec, b));
	}

	inline PSVector2f_s operator/(const PSVector2f_s& a, const PSVector2f_s& b)
	{
		return PSVector2f_s(_mm_div_ps(a.vec, b.vec));
	}

	inline PSVector2f_s operator/(const PSVector2f_s& a, const float& b)
	{
		__m128 scalar = _mm_set1_ps(b);
		return PSVector2f_s(_mm_div_ps(a.vec, scalar));
	}

	inline PSVector2f_s operator/(const PSVector2f_s& a, const __m128& b)
	{
		return PSVector2f_s(_mm_div_ps(a.vec, b));
	}

	inline int DotProduct(const PSVector2f_s& a, const PSVector2f_s& b)
	{
		__m128 result = _mm_dp_ps(a.vec, b.vec, 0xF1);
		return result.m128_f32[0];
	}

	inline PSVector2f_s Lerp(const PSVector2f_s& a, const PSVector2f_s& b, float c)
	{
		PSFloat x(lerp(a.vec.m128_f32[0], b.vec.m128_f32[0], c)), y(lerp(a.vec.m128_f32[1], b.vec.m128_f32[1], c));
		return PSVector2f_s(x.f32, y.f32);
	}

	inline PSVector2f_s Clamp(const PSVector2f_s& a, const PSVector2f_s& b, float c)
	{
		PSFloat x(clamp(a.vec.m128_f32[0], b.vec.m128_f32[0], c)), y(clamp(a.vec.m128_f32[1], b.vec.m128_f32[1], c));
		return PSVector2f_s(x.f32, y.f32);
	}
}

#endif
