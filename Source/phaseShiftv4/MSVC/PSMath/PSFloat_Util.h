#pragma once

#ifndef _PSFLOAT_UTIL_H_
#define _PSFLOAT_UTIL_H_

#include <cmath>
#include <limits>
#include <algorithm>

namespace PSMath
{
	typedef union
	{
		long long i64;
		float f32;
	} flt_32;

	inline float machine_eps(float value)
	{
		flt_32 s;
		s.f32 = value;
		s.i64++;
		return (s.i64 < 0 ? value - s.f32 : s.f32 - value);
	}

	inline bool DE_areEqualRel(float a, float b)
	{
		return (fabs(a - b) <= FLT_EPSILON * max(fabs(a), fabs(b)));
	}

	inline bool CE_areEqualRel(float a, float b)
	{
		return (fabs(a - b) <= machine_eps((a + b) / 2) * max(fabs(a), fabs(b)));
	}

	inline bool SE_areEqualREs(float a, float b, float epsilon = 0.1f)
	{
		return (fabs(a - b) <= epsilon * max(fabs(a), fabs(b)));
	}

	inline bool DE_areEqual(float a, float b)
	{
		return (fabs(a - b) <= FLT_EPSILON * max(1.0f, max(a, b)));
	}

	inline bool CE_areEqual(float a, float b)
	{
		return (fabs(a - b) <= machine_eps((a + b) / 2) * max(1.0f, max(a, b)));
	}

	inline bool SE_areEqual(float a, float b, float epsilon = 0.1f)
	{
		return (fabs(a - b) <= epsilon * max(1.0f, max(a, b)));
	}

	inline bool DE_areEqualAbs(float a, float b)
	{
		return (fabs(a - b) <= FLT_EPSILON);
	}

	inline bool CE_areEqualAbs(float a, float b)
	{
		return (fabs(a - b) <= machine_eps((a + b) / 2));
	}

	inline bool SE_areEqualAbs(float a, float b, float epsilon = 0.1f)
	{
		return (fabs(a - b) <= epsilon);
	}
}

#endif

