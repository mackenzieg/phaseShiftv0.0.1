#pragma once

#ifndef _PSMATH_H_
#define _PSMATH_H_

#include <assert.h>

#define PI					3.141592653589793238462643383279502884197169399375105820974
#define TAU					6.283185307179586476925286766559005768394338798750211641949
#define E					2.718281828459045235360287471352662497757247093699959574966
#define S_ROOT_2			1.414213562373095048801688724209698078569671875376948073176
#define S_ROOT_3			1.732050807568877293527446341505872366942805253810380628055
#define S_ROOT_5			2.236067977499789696409173668731276235440618359611525724270
#define LN_2				0.693147180559945309417232121458176568075500134360255254120
#define EULER_CONSTANT		0.577215664901532860606512090082402431042159335939923598805
#define GOLDEN_RATIO		1.618033988749894848204586834365638117720309179805762862135
#define INV_GOLDEN_RATIO	0.618033988749894848204586834365638117720309179805762862135

#define GAMMA				EULER_CONSTANT
#define PHI					GOLDEN_RATIO

#define HALFPI				PI / 2;
#define DOUBLEPI			PI * 2;
#define QUATERPI			PI / 4;
#define QUADPi				PI * 4;

#define PITORAD				PI / 180;
#define PITODEG				180 / PI;

namespace PSMath
{
	template <class T>
	T sqrtf(const T x)
	{
		union
		{
			int i;
			float x;
		} u;
		u.x = x;
		u.i = (1 << 29) + (u.i >> 1) - (1 << 22);

		u.x = u.x + x / u.x;
		u.x = 0.25f * u.x + x / u.x;

		return u.x;
	}

	template <class T>
	T invsqratf(T number)
	{
		long i;
		float x2, y;
		const float threehalfs = 1.5F;

		x2 = number * 0.5F;
		y = number;
		i = *reinterpret_cast<long *>(&y);
		i = 0x5f3759df - (i >> 1);
		y = *reinterpret_cast<float *>(&i);
		y = y * (threehalfs - (x2 * y * y));

		return y;
	}

	template <class T>
	inline T toRad(T a)
	{
		return a * PITORAD;
	}

	template <class T>
	inline T toDeg(T a)
	{
		return a * PITODEG;
	}

	template <typename T>
	inline T square(T value)
	{
		return value * value;
	}

	template <typename T>
	inline T cube(T value)
	{
		return value * value * value;
	}

	template <typename T>
	inline T quad(T value)
	{
		return value * value * value * value;
	}

	template <typename T>
	inline T penta(T value)
	{
		return value * value * value * value * value;
	}

	template <typename T>
	inline T Min(const T& a, const T& b)
	{
		return a <= b ? a : b;
	}

	template <typename T>
	inline T Max(const T& a, const T& b)
	{
		return a >= b ? a : b;
	}

	template <typename T>
	inline T Max(const T& a, const T& b, const T& c)
	{
		return Max(Max(a, b), c);
	}

	template <typename T>
	inline T Min(const T& a, const T& b, const T& c)
	{
		return Min(Min(a, b), c);
	}

	template <typename T>
	inline T Min(const T& a, const T& b, const T& c, const T& d)
	{
		return Min(Min(a, b), Min(c, d));
	}

	template <typename T>
	inline T Max(const T& a, const T& b, const T& c, const T& d)
	{
		return Max(Max(a, b), Max(c, d));
	}

	template <typename T>
	inline void swap(T& a, T& b)
	{
		T temp = a;
		a = b;
		b = temp;
	}

	template <typename T>
	inline T abs(const T& a)
	{
		return a >= 0 ? a : -a;
	}

	template <typename T, typename U>
	inline T lerp(T a, T b, U c)
	{
		assert(a < 1);
		assert(a > 0);
		return a + (b - a) * c;
	}

	template <typename T, typename U>
	inline T cubic_lerp(const T& a, const T& b, U s)
	{
		assert(a < 1);
		assert(a > 0);
		if (s < 0.0f) s = 0.0f;
		else if (s > 1.0f) s = 1.0f;
		return (a * ((2.0f * (s * s * s)) - (3.0f * (s * s)) + 1.0f)) + (b * ((3.0f * (s * s)) - (2.0f * (s * s * s))));
	}

	template <typename T>
	inline T clamp(const T& val, const T& floor, const T& ceil)
	{
		assert(floor < ceil);
		return val <= ceil ? (val >= floor ? val : floor) : ceil;
	}

	template <typename T>
	inline T clamp_low(T value, T low)
	{
		return (value < low) ? low : value;
	}

	template <typename T>
	inline T clamp_high(T value, T high)
	{
		return (value > high) ? high : value;
	}

	template <typename T>
	inline T saturate(T value)
	{
		return (value < 0.0f) ? 0.0f : ((value > 1.0f) ? 1.0f : value);
	}

	template <typename T>
	inline bool is_within_open_range(T a, T l, T h)
	{
		return (a >= l) && (a < h);
	}
}

#endif
